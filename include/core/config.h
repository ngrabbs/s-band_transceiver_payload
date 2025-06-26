// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

typedef struct {
    uint32_t housekeeping_interval_ms;
    uint32_t can_poll_interval_ms;
    uint32_t radio_tx_interval_ms;
    // Add more as needed
} system_config_t;

extern system_config_t sys_config;

void config_load_defaults(void);

#endif
