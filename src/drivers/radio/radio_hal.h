#ifndef RADIO_HAL_H
#define RADIO_HAL_H

#include <stdint.h>
#include <stdbool.h>

bool radio_hal_init(void);
bool radio_hal_set_frequency(uint32_t freq_hz);
bool radio_hal_set_power(uint8_t power_dbm);
bool radio_hal_set_modulation(uint8_t modulation);
bool radio_hal_set_bandwidth(uint32_t bw_reg);
bool radio_hal_set_spreading_factor(uint8_t sf_reg);
bool radio_hal_set_coding_rate(uint8_t cr_reg);
bool radio_hal_transmit(const uint8_t *data, uint8_t length);

#endif
