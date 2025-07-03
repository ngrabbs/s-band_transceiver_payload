#include "radio_hal.h"
#include "drivers/radio/peripheral_lora1280.h"
#include "peripheral_rfm9x.h"
#include "config.h"

bool radio_hal_init(void) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_init();
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_init();
    }
    return false;
}

bool radio_hal_set_frequency(uint32_t freq_hz) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_set_frequency(freq_hz);
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_set_frequency(freq_hz);
    }
    return false;
}

bool radio_hal_set_power(uint8_t power_dbm) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_set_power(power_dbm);
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_set_power(power_dbm);
    }
    return false;
}

bool radio_hal_set_modulation(uint8_t modulation) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_set_modulation(modulation);
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_set_modulation(modulation);
    }
    return false;
}

bool radio_hal_set_bandwidth(uint32_t bw_reg) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_set_bandwidth(bw_reg);
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_set_bandwidth(bw_reg);
    }
    return false;
}

bool radio_hal_set_spreading_factor(uint8_t sf_reg) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_set_spreading_factor(sf_reg);
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_set_spreading_factor(sf_reg);
    }
    return false;
}

bool radio_hal_set_coding_rate(uint8_t cr_reg) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_set_coding_rate(cr_reg);
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_set_coding_rate(cr_reg);
    }
    return false;
}

bool radio_hal_transmit(const uint8_t *data, uint8_t length) {
    if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        return lora1280_transmit(data, length);
    } else if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        return rfm9x_transmit(data, length);
    }
    return false;
}