// protocol_spacecan.c
#include "protocol_spacecan.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>


// Example binary beacon format (13 bytes):
// [0]   Type (1 byte)
// [1-2] Temperature (int16_t, 0.01°C units)
// [3-6] Uptime (uint32_t ms)
// [7-8] Free heap (uint16_t bytes / 32)
// [9]   Task count
// [10]  TX count
// [11]  RX count
// [12]  Reserved / checksum / flags

size_t protocol_spacecan_format_beacon(uint8_t *out, size_t max_len, const hk_telemetry_t *hk) {
    if (max_len < 13 || out == NULL || hk == NULL) return 0;

    memset(out, 0, 13);
    out[0] = SPACECAN_TYPE_BEACON;

    int16_t temp_encoded = (int16_t)(hk->temperature_c * 100);
    out[1] = (temp_encoded >> 8) & 0xFF;
    out[2] = temp_encoded & 0xFF;

    out[3] = (hk->uptime_ms >> 24) & 0xFF;
    out[4] = (hk->uptime_ms >> 16) & 0xFF;
    out[5] = (hk->uptime_ms >> 8) & 0xFF;
    out[6] = (hk->uptime_ms) & 0xFF;

    uint16_t heap_compact = (hk->heap_free_bytes / 32);
    out[7] = (heap_compact >> 8) & 0xFF;
    out[8] = heap_compact & 0xFF;

    out[9]  = hk->task_count;
    out[10] = hk->radio_tx_count;
    out[11] = hk->radio_rx_count;

    out[12] = 0x00; // Reserved / checksum placeholder

    return 13;
}

void send_spacecan_burst(void) {
    // TODO: replace with actual telemetry data later
    uint8_t fake_data[] = { 0x42, 0x61, 0x64, 0x5A, 0x00 };

    printf("[SPACECAN] Sending burst: ");
    for (int i = 0; i < sizeof(fake_data); ++i) {
        printf("%02X ", fake_data[i]);
    }
    printf("\n");

    // TODO: send over LoRa or CAN bus
}
