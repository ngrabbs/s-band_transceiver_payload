#ifndef PERIPHERAL_LORA1280_H
#define PERIPHERAL_LORA1280_H

#include <stdint.h>
#include <stdbool.h>
#include "sx1280_wrapper.h"

bool lora1280_init(void);
bool lora1280_transmit(const char* msg);

#endif