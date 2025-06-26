#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include "hardware/spi.h"

// === LoRa parameters ===
typedef struct {
    uint32_t rf_freq;
    int8_t tx_power;
    uint8_t lora_sf;
    uint8_t band_width;
    uint8_t code_rate;
    uint8_t payload_size;
} lora_params_t;

// === Task Timings ===
typedef struct {
    uint32_t housekeeping_interval_ms;
    uint32_t can_poll_interval_ms;
    uint32_t radio_tx_interval_ms;

} sys_config_t;

extern sys_config_t sys_config;

// === Pin Configuration ===
typedef struct {
    // SPI Bus and Chip Select
    spi_inst_t *spi_bus;
    uint32_t cs_lora;
    uint32_t cs_can;

    // SPI pins
    uint32_t spi_sck;
    uint32_t spi_mosi;
    uint32_t spi_miso;

    // LoRa specific
    uint32_t lora_reset;
    uint32_t lora_busy;
    uint32_t lora_dio1;

    // I2C
    uint32_t i2c_sda;
    uint32_t i2c_scl;

} pin_config_t;

// Global configuration instances
extern pin_config_t pin_config;
extern lora_params_t lora_config;
extern sys_config_t sys_config;

void config_load_defaults(void);

#endif
