//#include "hardware/spi.h"
#include "config.h"

// Global instances
pin_config_t pin_config;
radio_config_t lora_config;
radio_config_t rfm9x_config;
sys_config_t sys_config;

void config_load_defaults(void) {
    sys_config.housekeeping_interval_ms = 1000;
    sys_config.can_poll_interval_ms     = 100;
    sys_config.radio_tx_interval_ms = 100;
//    sys_config.radio_type = RADIO_TYPE_RFM9X;
    sys_config.radio_type = RADIO_TYPE_SX1280;

    // this spi works for the lora module on pico.
    // I dont know what it needs to be configured to
    // for adafruit rp2040 feather canbus
    pin_config.spi_bus0 = spi0;
    pin_config.spi_sck0 = 2;
    pin_config.spi_mosi0 = 3;
    pin_config.spi_miso0 = 4;

    // rp2040 feather canbus spi uses:
    pin_config.spi_bus1 = spi1;
    pin_config.spi_sck1 = 14;
    pin_config.spi_mosi1 = 15;
    pin_config.spi_miso1 = 8;


    pin_config.cs_lora = 5;
    pin_config.cs_can = 19;
    pin_config.rst_can = 18;
    pin_config.int_can = 22;

    /*
    pin_config.lora_reset = 22; // 25 maybe
    pin_config.lora_busy  = 26; // 24 maybe
    pin_config.lora_dio1  = 27; // 29 *A3* maybe
    */
    // testing config
    pin_config.lora_reset = 25; // 25 maybe
    pin_config.lora_busy  = 24; // 24 maybe
    pin_config.lora_dio1  = 29; // 29 *A3* maybe

    pin_config.i2c_sda = 10;
    pin_config.i2c_scl = 11;

    // LoRa radio parameters
    lora_config.rf_freq      = 2390000000;
    lora_config.tx_power     = 10;
    lora_config.modulation   = 0x01; // Lora
    lora_config.lora_sf      = 0x70; // SF7
    lora_config.band_width   = 0x34; // 200 kHz
    lora_config.code_rate    = 0x01; // 4/5
    lora_config.payload_size = 64;

        // LoRa radio parameters
    rfm9x_config.rf_freq      = 915000000;
    rfm9x_config.tx_power     = 15;
    rfm9x_config.modulation   = 0x01; // Lora
    rfm9x_config.lora_sf      = 0x70; // SF7
    rfm9x_config.band_width   = 0x08; // 250Khz = 0x08, 125 = 0x07
    rfm9x_config.code_rate    = 0x01; // 4/5
    rfm9x_config.payload_size = 64;
}

radio_config_t get_active_radio_config(void) {
    switch(sys_config.radio_type) {
        case RADIO_TYPE_RFM9X:
            return rfm9x_config;
        case RADIO_TYPE_SX1280:
            return lora_config;
        default:
            // Provide safe defaults or log error
            radio_config_t empty = {0};
            return empty;
    }
}