#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_MESSAGE_SIZE 64

typedef struct {
    uint8_t data[MAX_MESSAGE_SIZE];
    uint8_t length;
} message_t;

void message_queue_init(void);
bool message_queue_send(const message_t *msg);
bool message_queue_receive(message_t *msg);

#endif // MESSAGE_QUEUE_H