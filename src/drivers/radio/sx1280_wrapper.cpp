// sx1280_wrapper.cpp
// Thin C-callable wrapper around the C++ SX1280 object

#include "SX1280.h"
#include <cstring>
#include "config.h"

// Instantiate the SX1280 object with pins for NSS, RESET, BUSY, DIO1
// You can change these if needed
// static SX1280 radio(5, 22, 26, 27);  // NSS, RESET, BUSY, DIO1
static SX1280 radio;

extern "C" {

#include <stdint.h>
#include <stdbool.h>


bool sx1280_init() {
    return radio.Init();
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

