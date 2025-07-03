#include "drivers/radio/peripheral_lora1280.h"
#include "sx1280_wrapper.h"
#include <string.h>
#include <stdio.h>
#include "config.h"

bool lora1280_init(void) {
    return sx1280_init(&lora_config);
}


bool lora1280_set_frequency(uint32_t freq_hz) {
    printf("[LORA_CFG] Setting frequency: %u Hz\n", freq_hz);
    sx1280_set_frequency(freq_hz);
    return true;
}

bool lora1280_set_power(uint8_t power_dbm) {
    printf("[LORA_CFG] Setting power: %u dBm\n", power_dbm);
    sx1280_set_power(power_dbm);
    return true;
}

bool lora1280_set_modulation(uint8_t modulation) {
    printf("[LORA_CFG] Setting modulation: 0x%02X\n", modulation);
    sx1280_set_modulation(modulation);
    return true;
}

bool lora1280_set_bandwidth(uint32_t bw_hz) {
    // For now we just log and send register value directly as bandwidth code
    printf("[LORA_CFG] Setting bandwidth (reg code): 0x%02X\n", (uint8_t)bw_hz);
    sx1280_set_modulation_params(
        lora_config.lora_sf,
        (uint8_t)bw_hz,
        lora_config.code_rate
    );
    return true;
}

bool lora1280_set_spreading_factor(uint8_t sf) {
    printf("[LORA_CFG] Setting spreading factor (reg code): 0x%02X\n", sf);
    sx1280_set_modulation_params(
        sf,
        lora_config.band_width,
        lora_config.code_rate
    );
    return true;
}

bool lora1280_set_coding_rate(uint8_t cr) {
    printf("[LORA_CFG] Setting coding rate (reg code): 0x%02X\n", cr);
    sx1280_set_modulation_params(
        lora_config.lora_sf,
        lora_config.band_width,
        cr
    );
    return true;
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
