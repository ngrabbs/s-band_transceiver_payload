#include "peripheral_lora1280.h"

bool lora1280_init(void) {
    lora_params_t params = {
        .rf_freq = 2410000000,
        .tx_power = 2,
        .lora_sf = 12,
        .band_width = 1600,
        .code_rate = 1,
        .payload_size = 64
    };
    return sx1280_init(&params);
}

bool lora1280_transmit(const char* msg) {
    sx1280_tx(msg, strlen(msg));
    return sx1280_wait_tx_done();
}
