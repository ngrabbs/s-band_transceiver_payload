#include "freertos/task_radio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drivers/radio/peripheral_lora1280.h"
#include "drivers/radio/radio_hal.h"
#include <string.h>
#include <stdio.h>
#include "core/message_queue.h"
#include "config.h"

#define RADIO_TASK_STACK_SIZE 512
#define RADIO_TASK_PRIORITY   (tskIDLE_PRIORITY + 2)

static void radio_task(void *pvParameters) {

    bool ok = radio_hal_init();
    printf("[RADIO_INIT] radio_hal_init returned: %s\n", ok ? "OK" : "FAIL");

    // Generic defaults (safe starting values)
    uint32_t last_freq = 915000000;    // Default frequency e.g. 915 MHz for RFM9x
    uint8_t last_power = 10;           // Default power
    uint8_t last_mod = 0x01;           // Default modulation: LoRa
    uint32_t last_bw = 406000;         // Default bandwidth
    uint8_t last_sf = 7;               // Default SF
    uint8_t last_cr = 5;               // Default coding rate

    for (;;) {
        radio_message_t msg;

        if (message_queue_receive(&msg)) {

            switch (msg.type) {
                case RADIO_MSG_CONFIGURE:
                    printf("[RADIO] CONFIGURE message received.\n");

                    // Apply new config if set
                    last_freq = msg.body.config.frequency_hz;
                    last_power = msg.body.config.power_dbm;
                    last_mod = msg.body.config.modulation;
                    last_bw = msg.body.config.bandwidth_hz;
                    last_sf = msg.body.config.spreading_factor;
                    last_cr = msg.body.config.coding_rate;

                    radio_hal_set_frequency(last_freq);
                    radio_hal_set_power(last_power);
                    radio_hal_set_modulation(last_mod);
                    radio_hal_set_bandwidth(last_bw);
                    radio_hal_set_spreading_factor(last_sf);
                    radio_hal_set_coding_rate(last_cr);

                    break;

                case RADIO_MSG_SEND_DATA:
                    printf("[RADIO] TX binary (%d bytes): ", msg.body.payload.length);
                    for (int i = 0; i < msg.body.payload.length; i++) {
                        printf("%02X ", msg.body.payload.data[i]);
                    }
                    printf("\n");

                    {
                        uint8_t header[4] = {0xFF, 0xFF, 0x00, 0x00};

                        uint8_t tx_buf[256];
                        size_t total_len = 0;

                        memcpy(tx_buf, header, 4);
                        memcpy(tx_buf + 4, msg.body.payload.data, msg.body.payload.length);
                        total_len = msg.body.payload.length + 4;

                        printf("[RADIO] Transmitting %zu bytes with RadioHead header.\n", total_len);
                        radio_hal_transmit(tx_buf, total_len);
                    }
                    break;

                default:
                    printf("[RADIO] Unknown message type: %d\n", msg.type);
                    break;
            }
        } else {
            printf("[Radio Task] No message received\n");
        }

        vTaskDelay(pdMS_TO_TICKS(sys_config.radio_tx_interval_ms));
    }
}

void launch_radio_task(void) {
    xTaskCreate(
        radio_task,
        "RadioTask",
        RADIO_TASK_STACK_SIZE,
        NULL,
        RADIO_TASK_PRIORITY,
        NULL
    );
}