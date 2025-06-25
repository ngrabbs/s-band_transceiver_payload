// peripheral_mcp2515.h - Header for MCP2515 CAN controller interface
#ifndef PERIPHERAL_MCP2515_H
#define PERIPHERAL_MCP2515_H

#include <stdint.h>
#include <stdbool.h>

// Register access
void mcp2515_select(void);
void mcp2515_deselect(void);
uint8_t mcp2515_read_register(uint8_t address);
void mcp2515_write_register(uint8_t address, uint8_t value);
void mcp2515_reset(void);

// Initialization for 8MHz crystal and 500 kbps CAN
bool mcp2515_configure_8mhz_500k(void);
bool mcp2515_configure_8mhz_250k(void);

#endif // PERIPHERAL_MCP2515_H
