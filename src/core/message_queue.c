#include "FreeRTOS.h"
#include "queue.h"
#include "core/message_queue.h"
#include <stdio.h>

QueueHandle_t radio_queue;

void message_queue_init(void) {
    radio_queue = xQueueCreate(5, sizeof(message_t));
}

bool message_queue_send(const message_t *msg) {
    printf("[QUEUE] Sending message of length %d\n", msg->length);
    return xQueueSend(radio_queue, msg, 0) == pdPASS;
}

bool message_queue_receive(message_t *msg) {
    printf("[QUEUE] Receiving message of length %d\n", msg->length);
    return xQueueReceive(radio_queue, msg, portMAX_DELAY) == pdPASS;
}
