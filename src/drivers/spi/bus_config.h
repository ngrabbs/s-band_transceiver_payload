#ifndef BUS_CONFIG_H
#define BUS_CONFIG_H

#include "config.h"

#define SPI_BUS0       pin_config.spi_bus0
#define SPI_SCK_PIN0   pin_config.spi_sck0
#define SPI_MOSI_PIN0  pin_config.spi_mosi0
#define SPI_MISO_PIN0  pin_config.spi_miso0

#define SPI_BUS1       pin_config.spi_bus0
#define SPI_SCK_PIN1   pin_config.spi_sck0
#define SPI_MOSI_PIN1  pin_config.spi_mosi0
#define SPI_MISO_PIN1  pin_config.spi_miso0

void init_spi(void);

#endif // BUS_CONFIG_H