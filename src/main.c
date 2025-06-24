#include "pico/stdlib.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "init_tasks.h"

int main() {
    stdio_init_all();
    sleep_ms(5000);
    printf("main.c done sleeping fire it up\n");

    init_spi();
//    init_canbus();
    init_tasks();
    vTaskStartScheduler();
    while (1) {
        // Should never reach here
    }
    return 0;
}


