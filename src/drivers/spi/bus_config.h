#ifndef BUS_CONFIG_H
#define BUS_CONFIG_H

#include "config.h"

#define SPI_BUS       pin_config.spi_bus
#define SPI_SCK_PIN   pin_config.spi_sck
#define SPI_MOSI_PIN  pin_config.spi_mosi
#define SPI_MISO_PIN  pin_config.spi_miso

void init_spi(void);

#endif // BUS_CONFIG_H