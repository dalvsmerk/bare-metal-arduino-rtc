#include "rtc.h"
#include "pin.h"
#include "util/delay.h"

#define DELAY_MS 1 // reconsider shorter delay if possible (using baud rate)
#define CENTURY 2000

#define clk_cycle(clk_pin) \
  do {                     \
    pin_high(clk_pin);     \
    _delay_ms(DELAY_MS);   \
    pin_low(clk_pin);      \
    _delay_ms(DELAY_MS);   \
  } while(0)              

void rtc_init(spi_t *io) {
  pin_mode(io->clk, OUTPUT);
  // Call pin_mode(DATA, <OUTPUT or INPUT>); when reading/writing data from pin
  pin_mode(io->ce, OUTPUT);
}

uint8_t rtc_read(spi_t *io, rtc_cmd_read_t cmd) {
  pin_low(io->clk);
  pin_high(io->ce);
  
  // Write read-command byte
  pin_mode(io->data, OUTPUT);

  for (int bit = 0; bit < 8; bit++) {
    pin_write(io->data, cmd & 0x80);
    clk_cycle(io->clk);

    cmd = cmd << 1;
  }

  // Read byte from RTC
  pin_mode(io->data, INPUT);
  uint8_t data = 0;

  for (int bit = 7; bit >= 0; bit--) {
    clk_cycle(io->clk);

    data |= (pin_read(io->data) << bit);
  }

  pin_low(io->ce);

  return data;
}

uint8_t rtc_read_year(spi_t *io) {
  uint8_t year_raw = rtc_read(io, YEAR_R);
  return year_raw;

  // uint8_t year_ones = year_raw << 4;
  // uint8_t year_tens = year_raw >> 4;
  // Converting to CENTURY + year_tens + year_ones requires uint16_t
  // return year_tens + year_ones;
}

void rtc_write(spi_t *io, rtc_cmd_write_t cmd, uint8_t data) {
  // TODO
  
  pin_mode(io->data, OUTPUT);
  pin_low(io->clk); // make sure CLK is low before we enable data transfer
  pin_high(io->ce);

  for (uint8_t bit = 0; bit < 8; bit++) {
    pin_write(io->data, cmd & 0x80);
    clk_cycle(io->clk);

    cmd = cmd << 1;
  }

  for (uint8_t bit = 0; bit < 8; bit++) {
    // mega328p is little-endian so LSB bit is on the far-left
    pin_write(io->data, data & 0x80);
    clk_cycle(io->clk);
    
    data = data << 1;
  }

  pin_low(io->ce);
}
