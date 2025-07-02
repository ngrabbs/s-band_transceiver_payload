// task_can.c - FreeRTOS task that initializes and monitors MCP2515
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "drivers/can/peripheral_mcp2515.h"
#include "hardware/spi.h"
#include <stdio.h>

#define MCP2515_SPI spi0

void can_task(void *params)
{
    printf("[CAN TASK] Starting CAN task...\n");

    if (!can_init())
    {
        printf("[CAN TASK] MCP2515 config failed\n");
        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    while (1)
    {
        can_frame_t frame;
        if (can_receive(&frame))
        {
            printf("Received CAN Frame: ID=0x%lX DLC=%d Data:", frame.id, frame.dlc);
            for (int i = 0; i < frame.dlc; i++)
            {
                printf(" %02X", frame.data[i]);
            }
            printf("\n");
        }
        int quit = getchar_timeout_us(0);
        if (quit == 'q')
        {
            printf("Exiting CAN Receive Mode.\n");
            break;
        }
        sleep_ms(10);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void launch_can_task(void)
{
    xTaskCreate(
        can_task,
        "CAN Task",
        1024,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL);
}