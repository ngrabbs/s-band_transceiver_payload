#ifndef PERIPHERAL_LORA1280_H
#define PERIPHERAL_LORA1280_H

#include <stdint.h>
#include <stdbool.h>
#include "drivers/radio/sx1280_wrapper.h"

bool lora1280_init(void);
bool lora1280_transmit(const uint8_t *data, uint8_t len);
bool lora1280_set_frequency(uint32_t freq_hz);
bool lora1280_set_power(uint8_t power_dbm);
bool lora1280_set_modulation(uint8_t modulation);
bool lora1280_set_bandwidth(uint32_t bw_hz);
bool lora1280_set_spreading_factor(uint8_t sf);
bool lora1280_set_coding_rate(uint8_t cr);

#endif