#ifndef SX1280_WRAPPER_H
#define SX1280_WRAPPER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t rf_freq;
    int8_t   tx_power;
    uint8_t  lora_sf;
    uint8_t  band_width;
    uint8_t  code_rate;
    uint8_t  payload_size;
} lora_params_t;

/**
 * Initialize the SX1280 radio with the specified parameters.
 * Returns true on success.
 */
bool sx1280_init(const lora_params_t* params);

/**
 * Transmit a raw buffer over LoRa.
 */
void sx1280_tx(const char* msg, uint16_t len);

/**
 * Wait for TX_DONE interrupt from the radio.
 * Returns true if TX completed successfully.
 */
bool sx1280_wait_tx_done(void);

/**
 * Issue a software reset to the radio.
 */
void sx1280_reset(void);

#ifdef __cplusplus
}
#endif

#endif // SX1280_WRAPPER_H
