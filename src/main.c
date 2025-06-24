#include "pico/stdlib.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "init_tasks.h"

int main() {
    stdio_init_all();

    init_spi();
//    init_canbus();
    init_tasks();
    vTaskStartScheduler();
    while (1) {
        // Should never reach here
    }
    return 0;
}


