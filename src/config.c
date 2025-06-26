// config.c
#include "config.h"

system_config_t sys_config;

void config_load_defaults(void) {
    sys_config.housekeeping_interval_ms = 10000;
    sys_config.can_poll_interval_ms     = 200;
    sys_config.radio_tx_interval_ms     = 10000;
}
