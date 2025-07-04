// task_can.c - FreeRTOS task that initializes and monitors MCP2515
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "drivers/can/peripheral_mcp2515.h"
#include "protocols/protocol_spacecan.h"
#include "protocols/spacecan_assembler.h"
#include "hardware/spi.h"
#include <stdio.h>
#include "debug.h"

#define MCP2515_SPI spi0

void can_task(void *params)
{
    DEBUG_INFO("[CAN TASK] Starting CAN task...\n");

    if (!can_init())
    {
        DEBUG_ERROR("[CAN TASK] MCP2515 config failed\n");
        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    while (1)
    {
        can_frame_t frame;
        if (can_receive(&frame)) {
            spacecan_assembler_handle(&frame);
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