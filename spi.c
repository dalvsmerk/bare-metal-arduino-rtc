#include "spi.h"
#include "pin.h"
#include "util/delay.h"

#define DELAY_MS 1 // reconsider shorter delay if possible

void spi_init(spi_t *io) {
  pin_mode(io->clk, OUTPUT);
  // Call pin_mode(DATA, <OUTPUT or INPUT>); when reading/writing data from pin
  pin_mode(io->ce, OUTPUT);
}

uint8_t spi_read(spi_t *io) {}

void spi_write(spi_t *io, uint8_t data) {
  pin_mode(io->data, OUTPUT);
  pin_low(io->clk); // make sure CLK is low before we enable data transfer
  pin_high(io->ce);

  for (uint8_t bit = 0; bit < 8; bit++) {
    // mega328p is little-endian so LSB bit is on the far-left
    pin_set(io->data, data & 0x80);

    pin_high(io->clk);
    _delay_ms(DELAY_MS);
    pin_low(io->clk);
    _delay_ms(DELAY_MS);
    
    data = data << 1;
  }

  pin_low(io->ce);
}
