#include "peripheral_lora1280.h"
#include "sx1280_wrapper.h"
#include "lora_defs.h"
#include <string.h>
#include <stdio.h>

bool lora1280_init(void) {
    lora_params_t params = {
        .rf_freq = 2250050000,
        .tx_power = 0,
        .lora_sf = 0x70, // sf 7
        .band_width = 0x34, // 0200 bandwidth
        .code_rate = 0x01, // cr 4/5
        .payload_size = 64
    };
    return sx1280_init(&params);
}

bool lora1280_transmit(const uint8_t *data, uint8_t len) {
    printf("[LORA_TX] Transmitting (%d bytes): ", len);
    for (int i = 0; i < len; ++i){
        printf("%02X ", data[i]);
    }
    printf("\n");

    sx1280_tx(data, len);
    return sx1280_wait_tx_done();
}
