#include "core/message_queue.h"
#include "config.h"
#include "init_tasks.h"
#include "freertos/task_radio.h"
#include "freertos/task_can.h"
#include "freertos/task_housekeeping.h"

void init_tasks(void) {
    launch_radio_task();
    launch_can_task();
    launch_housekeeping_task();

    // Fetch the active radio config based on sys_config.radio_type
    radio_config_t active_cfg = get_active_radio_config();

    radio_message_t config_msg = {
        .type = RADIO_MSG_CONFIGURE,
        .body.config.frequency_hz = active_cfg.rf_freq,
        .body.config.power_dbm = active_cfg.tx_power,
        .body.config.modulation = active_cfg.modulation,
        .body.config.bandwidth_hz = active_cfg.band_width,
        .body.config.spreading_factor = active_cfg.lora_sf,
        .body.config.coding_rate = active_cfg.code_rate
    };


    message_queue_send(&config_msg);
}