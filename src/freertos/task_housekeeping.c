// task_housekeeping.c
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "freertos/task_housekeeping.h"
#include "subsystems/housekeeping/housekeeping.h"
#include "protocols/protocol_spacecan.h"
#include "core/config.h"
#include "core/message_queue.h"
#include <string.h>

void housekeeping_task(void *params) {
    printf("[HOUSEKEEPING] Starting housekeeping task...\n");
    housekeeping_init();

    while (1) {
        printf("[HOUSEKEEPING] Collecting system data... every %lums\n", sys_config.housekeeping_interval_ms);
        uint8_t beacon_frame[16];
        hk_telemetry_t hk = collect_housekeeping_data();
        size_t len = protocol_spacecan_format_beacon(beacon_frame, sizeof(beacon_frame), &hk);

        // Wrap the payload in message_t
        message_t msg;
        msg.length = len;
        memcpy(msg.data, beacon_frame, msg.length);
        message_queue_send(&msg);

        printf("[HK] Temp %.2fC, Uptime: %lums, Free Heap: %u, Tasks: %d\n",
            hk.temperature_c, hk.uptime_ms, (unsigned)hk.heap_free_bytes, hk.task_count);

        printf("[SPACECAN] Beacon payload (%zu bytes): ", len);
        for (size_t i = 0; i < len; ++i) {
            printf("%02X ", beacon_frame[i]);
        }
        printf("\n");


        vTaskDelay(pdMS_TO_TICKS(sys_config.housekeeping_interval_ms));
    }
}

void launch_housekeeping_task(void) {
    xTaskCreate(
        housekeeping_task,
        "Housekeeping",
        512,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}
