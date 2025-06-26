#include "pico/stdlib.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "init_tasks.h"
#include "bus_config.h"
#include "message_queue.h"
#include "config.h"

int main() {
    stdio_init_all();
    sleep_ms(5000);

    config_load_defaults();
    init_spi();
//    init_canbus();

    message_queue_init();
    init_tasks();
    vTaskStartScheduler();
    while (1) {
        // Should never reach here
    }
    return 0;
}


