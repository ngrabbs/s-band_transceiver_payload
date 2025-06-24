#include "bus_config.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>

void init_spi() {
    printf("[SPI_INIT] setting up spi\n");
    spi_init(SPI_BUS, 1000000);
    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);
}
