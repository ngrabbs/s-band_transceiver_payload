#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_RADIO_PAYLOAD_SIZE 256

typedef enum {
    RADIO_MSG_CONFIGURE,
    RADIO_MSG_SEND_DATA
} radio_msg_type_t;

typedef struct {
    radio_msg_type_t type;

    union {
        struct {
            uint32_t frequency_hz;
            uint8_t power_dbm;
            uint8_t modulation;
            uint32_t bandwidth_hz;
            uint8_t spreading_factor;
            uint8_t coding_rate;
        } config;

        struct {
            uint8_t length;
            uint8_t data[MAX_RADIO_PAYLOAD_SIZE];
        } payload;
    } body;
} radio_message_t;

void message_queue_init(void);
bool message_queue_send(const radio_message_t *msg);
bool message_queue_receive(radio_message_t *msg);

#endif // MESSAGE_QUEUE_H