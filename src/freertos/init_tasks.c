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

    radio_message_t config_msg = {
        .type = RADIO_MSG_CONFIGURE,
        .body.config.frequency_hz = lora_config.rf_freq,
        .body.config.power_dbm = lora_config.tx_power,
        .body.config.modulation = 0x01, // LoRa
        .body.config.bandwidth_hz = lora_config.band_width,
        .body.config.spreading_factor = lora_config.lora_sf,
        .body.config.coding_rate = lora_config.code_rate
    };

    message_queue_send(&config_msg);
}