#include "bus_config.h"
#include "hardware/spi.h"

void init_spi() {
    spi_init(SPI_BUS, 1000000);
    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);
}
