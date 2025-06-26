// sx1280_wrapper.cpp
// Thin C-callable wrapper around the C++ SX1280 object

#include "SX1280.h"
#include <cstring>
#include "config.h"

// Instantiate the SX1280 object with pins for NSS, RESET, BUSY, DIO1
// You can change these if needed
//static SX1280 radio(5, 22, 26, 27);  // NSS, RESET, BUSY, DIO1
static SX1280 radio(pin_config.cs_lora, pin_config.lora_reset, pin_config.lora_busy, pin_config.lora_dio1);  // NSS, RESET, BUSY, DIO1
static loRa_Para_t saved_params;

extern "C" {

#include <stdint.h>
#include <stdbool.h>


bool sx1280_init(const lora_params_t* params) {
    loRa_Para_t saved_params;
    saved_params.rf_freq     = params->rf_freq;
    saved_params.tx_power    = params->tx_power;
    saved_params.lora_sf     = params->lora_sf;
    saved_params.band_width  = params->band_width;
    saved_params.code_rate   = params->code_rate;
    saved_params.payload_size = params->payload_size;

    return radio.Init(&saved_params);
}

void sx1280_tx(const char* msg, uint16_t len) {
    radio.TxPacket((uint8_t*)msg, len);
}

bool sx1280_wait_tx_done(void) {
    return radio.WaitForIRQ_TxDone();
}

void sx1280_reset(void) {
    radio.Reset_SX1280();
}

}

