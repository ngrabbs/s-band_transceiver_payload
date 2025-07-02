// peripheral_mcp2515.h - Header for MCP2515 CAN controller interface
#ifndef PERIPHERAL_MCP2515_H
#define PERIPHERAL_MCP2515_H

#include <stdint.h>
#include "config.h"

#define MCP2515_CS pin_config.cs_can
#define SPI_PORT1 pin_config.spi_bus1
#define SPI_BAUDRATE 1000000
#define PIN_SCK pin_config.spi_sck1
#define PIN_MOSI pin_config.spi_mosi1
#define PIN_MISO pin_config.spi_miso1

typedef struct {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
} can_frame_t;

int can_init(void);
void can_send(const can_frame_t* frame);
bool can_receive(can_frame_t* frame);

#endif // PERIPHERAL_MCP2515_H
