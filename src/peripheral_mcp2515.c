// peripheral_mcp2515.c - SPI driver for MCP2515 CAN controller
#include "peripheral_mcp2515.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

#define MCP2515_SPI       spi0
#define MCP2515_CS_PIN    6

void mcp2515_select() {
    gpio_put(MCP2515_CS_PIN, 0);
}

void mcp2515_deselect() {
    gpio_put(MCP2515_CS_PIN, 1);
}

uint8_t mcp2515_read_register(uint8_t address) {
    uint8_t tx[] = { 0x03, address, 0x00 };
    uint8_t rx[3];
    mcp2515_select();
    spi_write_read_blocking(MCP2515_SPI, tx, rx, 3);
    mcp2515_deselect();
    return rx[2];
}

void mcp2515_write_register(uint8_t address, uint8_t value) {
    uint8_t tx[] = { 0x02, address, value };
    mcp2515_select();
    spi_write_blocking(MCP2515_SPI, tx, 3);
    mcp2515_deselect();
}

void mcp2515_reset() {
    uint8_t cmd = 0xC0;
    mcp2515_select();
    spi_write_blocking(MCP2515_SPI, &cmd, 1);
    mcp2515_deselect();
    sleep_ms(10);
    printf("[MCP2515] Reset issued\n");
}

bool mcp2515_configure_8mhz_500k(void) {
    mcp2515_reset();

    gpio_init(MCP2515_CS_PIN);
	gpio_set_dir(MCP2515_CS_PIN, GPIO_OUT);
	gpio_put(MCP2515_CS_PIN, 1);

    // CNF1, CNF2, CNF3 calculated for 8 MHz clock and 500 kbps
    // TQ = 8 * (BRP + 1) / Fosc = 8 * (1+1) / 8e6 = 2 us
    // Bitrate = 1 / (TQ * total TQ count) = 1 / (2us * 8) = 500 kbps

    mcp2515_write_register(0x2A, 0x00); // CNF1: SJW=1TQ, BRP=1
    mcp2515_write_register(0x29, 0x90); // CNF2: BTLMODE=1, PHSEG1=4, PRSEG=1
    mcp2515_write_register(0x28, 0x02); // CNF3: PHSEG2=3

    mcp2515_write_register(0x0F, 0x00); // CANCTRL: Set to Normal mode

    // Verify CANSTAT mode bits (bits 7-5 == 000 for normal)
    uint8_t stat = mcp2515_read_register(0x0E);
    if ((stat & 0xE0) == 0x00) {
        printf("[MCP2515] Configured for 500kbps with 8MHz crystal\n");
        return true;
    } else {
        printf("[MCP2515] Failed to enter normal mode, status=0x%02X\n", stat);
        return false;
    }
}

bool mcp2515_configure_8mhz_250k(void) {
    mcp2515_reset();

    // CNF1, CNF2, CNF3 for 8 MHz oscillator and 250 kbps bitrate
    // Based on Microchip MCP2515 datasheet bit timing calculator
    // TQ = 2us, 16 TQ per bit = 2us * 16 = 250kbps

    mcp2515_write_register(0x2A, 0x01); // CNF1: SJW=1TQ, BRP=1
    mcp2515_write_register(0x29, 0xB8); // CNF2: BTLMODE=1, PHSEG1=6, PRSEG=2
    mcp2515_write_register(0x28, 0x05); // CNF3: PHSEG2=6

    mcp2515_write_register(0x0F, 0x00); // CANCTRL: Normal mode

    uint8_t stat = mcp2515_read_register(0x0E);
    if ((stat & 0xE0) == 0x00) {
        printf("[MCP2515] Configured for 250kbps with 8MHz crystal\n");
        return true;
    } else {
        printf("[MCP2515] Failed to enter normal mode, status=0x%02X\n", stat);
        return false;
    }
}
