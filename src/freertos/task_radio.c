#include "freertos/task_radio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drivers/radio/peripheral_lora1280.h"   // or your peripheral_lora1280.h
#include <string.h>
#include <stdio.h>
#include "core/config.h"
#include "core/message_queue.h"

#define RADIO_TASK_STACK_SIZE 512
#define RADIO_TASK_PRIORITY   (tskIDLE_PRIORITY + 2)

static void radio_task(void *pvParameters) {

    bool ok = lora1280_init();
    printf("[LORA_INIT] sx1280_init returned: %s\n", ok ? "OK" : "FAIL");

    for (;;) {
        message_t msg;
        if (message_queue_receive(&msg)) {
            //printf("[Radio Task] TX: %.*s\n", msg.length, msg.data);
            printf("[Radio Task] TX binary (%d bytes): ", msg.length);
            for (int i = 0; i < msg.length; i++) {
                printf("%02X ", msg.data[i]);
            }
            printf("\n");
            lora1280_transmit(msg.data, msg.length);  // assumes transmit casts to uint8_t*
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