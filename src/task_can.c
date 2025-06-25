// task_can.c - FreeRTOS task that initializes and monitors MCP2515
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "peripheral_mcp2515.h"
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
        // Read RX status
        printf("[CAN TASK] Checking for CAN\n");
        mcp2515_select();
        uint8_t cmd = 0xB0; // RX Status command
        uint8_t rx_buf[2];
        spi_write_read_blocking(MCP2515_SPI, &cmd, rx_buf, 2);
        mcp2515_deselect();

        uint8_t rx_status = rx_buf[1];
        if (rx_status & 0xC0) { // Check RXB0 or RXB1 has data
            printf("[CAN TASK] Frame available! RX_STATUS=0x%02X\n", rx_status);

            // Read RXB0 (0x90 is Read RXB0 command)
            mcp2515_select();
            uint8_t rxb0_cmd = 0x90;
            uint8_t buffer[14] = {0};
            spi_write_read_blocking(spi0, &rxb0_cmd, buffer, sizeof(buffer));
            mcp2515_deselect();

            printf("[CAN TASK] Raw Frame: ");
            for (int i = 1; i < sizeof(buffer); ++i) {
                printf("%02X ", buffer[i]);
            }
            printf("\n");
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void launch_can_task(void) {
    xTaskCreate(
        can_task,
        "CAN Task",
        512,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}
