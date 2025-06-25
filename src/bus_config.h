#ifndef BUS_CONFIG_H
#define BUS_CONFIG_H

#define SPI_BUS       spi0
#define SPI_SCK_PIN   2
#define SPI_MOSI_PIN  3
#define SPI_MISO_PIN  4

void init_spi(void);

#endif // BUS_CONFIG_H