#include "init_tasks.h"
#include "task_radio.h"
// #include "task_can.h"
// #include "task_housekeeping.h"

void init_tasks(void) {
    launch_radio_task();
    // launch_can_task();
    // launch_housekeeping_task();
}