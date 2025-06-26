// task_can.c - FreeRTOS task that initializes and monitors MCP2515
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "drivers/can/peripheral_mcp2515.h"
#include "hardware/spi.h"
#include <stdio.h>

#define MCP2515_SPI spi0

void can_task(void *params) {
    printf("[CAN TASK] Starting CAN task...\n");

    if (!mcp2515_configure_8mhz_250k()) {
        printf("[CAN TASK] MCP2515 config failed\n");
        while (1) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    printf("[CAN TASK] MCP2515 ready, entering loop...\n");

    while (1) {
        // Dump CANINTF
        uint8_t canintf = mcp2515_read_register(0x2C);
        printf("[CAN TASK] CANINTF = 0x%02X\n", canintf);

        // Dump CANSTAT
        uint8_t canstat = mcp2515_read_register(0x0E);
        printf("[CAN TASK] CANSTAT = 0x%02X (OPMODE = 0x%02X)\n", canstat, canstat & 0xE0);

        // Check RXB0
        if (canintf & 0x01) {
            printf("[CAN TASK] RXB0 has a message\n");
            mcp2515_select();
            uint8_t cmd = 0x90;
            uint8_t buf[14] = {0};
            spi_write_read_blocking(MCP2515_SPI, &cmd, buf, sizeof(buf));
            mcp2515_deselect();

            printf("[CAN TASK] RXB0 Frame: ");
            for (int i = 1; i < sizeof(buf); ++i) {
                printf("%02X ", buf[i]);
            }
            printf("\n");

            // Clear RX0IF
            mcp2515_write_register(0x2C, canintf & ~(0x01));
        }

        // Check RXB1
        if (canintf & 0x02) {
            printf("[CAN TASK] RXB1 has a message\n");
            mcp2515_select();
            uint8_t cmd = 0x94;
            uint8_t buf[14] = {0};
            spi_write_read_blocking(MCP2515_SPI, &cmd, buf, sizeof(buf));
            mcp2515_deselect();

            printf("[CAN TASK] RXB1 Frame: ");
            for (int i = 1; i < sizeof(buf); ++i) {
                printf("%02X ", buf[i]);
            }
            printf("\n");

            // Clear RX1IF
            mcp2515_write_register(0x2C, canintf & ~(0x02));
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void launch_can_task(void) {
    xTaskCreate(
        can_task,
        "CAN Task",
        1024,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}