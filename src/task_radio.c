#include "task_radio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "peripheral_lora1280.h"   // or your peripheral_lora1280.h
#include <string.h>
#include <stdio.h>

#define RADIO_TASK_STACK_SIZE 512
#define RADIO_TASK_PRIORITY   (tskIDLE_PRIORITY + 2)

static void radio_task(void *pvParameters) {
    const char *msg = "Cubesat@MSU TX Burst\n";

    bool ok = lora1280_init();
    printf("[LORA_INIT] sx1280_init returned: %s\n", ok ? "OK" : "FAIL");

    for (;;) {
        printf("transmit result %d\n", lora1280_transmit("testing 123"));
        printf("[Radio Task] TX complete\n");

        vTaskDelay(pdMS_TO_TICKS(10000));  // repeat every 10s
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