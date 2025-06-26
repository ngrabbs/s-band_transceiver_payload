// protocol_spacecan.h
#ifndef PROTOCOL_SPACECAN_H
#define PROTOCOL_SPACECAN_H

#include "subsystems/housekeeping/housekeeping.h"
#include <stdint.h>
#include <stddef.h>

// SpaceCAN beacon type
#define SPACECAN_TYPE_BEACON 0x01


// Output: fills `out` with bytes and returns how many were written
size_t protocol_spacecan_format_beacon(uint8_t *out, size_t max_len, const hk_telemetry_t *hk);


void send_spacecan_burst(void);

#endif
