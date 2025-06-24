#include "peripheral_lora1280.h"
#include "sx1280_wrapper.h"
#include "lora_defs.h"
#include <string.h>
#include <stdio.h>

bool lora1280_init(void) {
    lora_params_t params = {
        .rf_freq = 2250000000,
        .tx_power = 13,
        .lora_sf = 12,
        .band_width = LORA_BW_1600,
        .code_rate = 1,
        .payload_size = 64
    };
    return sx1280_init(&params);
}

bool lora1280_transmit(const char* msg) {
    printf("[LORA_TX] TRansmitting: %s\n", msg);
    sx1280_tx(msg, strlen(msg));
    return sx1280_wait_tx_done();
}
