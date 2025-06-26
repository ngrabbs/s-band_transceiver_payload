#include "drivers/radio/peripheral_lora1280.h"
#include "sx1280_wrapper.h"
#include "lora_defs.h"
#include <string.h>
#include <stdio.h>
#include "config.h"

bool lora1280_init(void) {
    return sx1280_init(&lora_config);
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
