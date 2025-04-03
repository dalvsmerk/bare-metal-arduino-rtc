#include "rtc.h"
#include "pin.h"
#include "util/delay.h"

void rtc_init(spi_t *io) {
  pin_mode(io->clk, OUTPUT);
  // Call pin_mode(DATA, <OUTPUT or INPUT>); when reading/writing data from pin
  pin_mode(io->data, INPUT);
  pin_mode(io->ce, OUTPUT);
  
  // Enable write to registers
  rtc_write(io, WriteWriteProtect, 0x0);
}

uint8_t rtc_read(spi_t *io, rtc_cmd_t cmd) {
  pin_low(io->clk);
  pin_high(io->ce);
  
  // Write read-command byte
  pin_mode(io->data, OUTPUT);

  for (int bit = 0; bit < 8; bit++) {
    pin_write(io->data, cmd & 0x01);

    if (bit < 7) {
      CLK_CYCLE(io->clk);
      cmd = cmd >> 1;
    } else {
      // prepare to read from rtc leaving clk pin high
      pin_high(io->clk);
    }
  }

  // Read byte from RTC
  pin_mode(io->data, INPUT);
  uint8_t data = 0;

  for (int bit = 0; bit < 8; bit++) {
    CLK_CYCLE(io->clk);
    data |= (pin_read(io->data) << bit);
  }

  pin_low(io->ce);

  return data;
}

void rtc_write(spi_t *io, rtc_cmd_t cmd, uint8_t data) {
  pin_mode(io->data, OUTPUT);
  pin_low(io->clk); // make sure CLK is low before we enable data transfer
  pin_high(io->ce);

  for (uint8_t bit = 0; bit < 8; bit++) {
    pin_write(io->data, cmd & 0x01);
    CLK_CYCLE(io->clk);

    cmd >>= 1;
  }

  for (uint8_t bit = 0; bit < 8; bit++) {
    pin_write(io->data, data & 0x01);
    CLK_CYCLE(io->clk);
    
    data >>= 1;
  }

  pin_low(io->ce);
}

void rtc_burst_read(spi_t *io, rtc_datetime_t *dst) {
  uint8_t cmd = ReadBurstClock;

  pin_low(io->clk);
  pin_high(io->ce);

  // Send command LSB-first
  pin_mode(io->data, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pin_write(io->data, cmd & 0x01);
    CLK_CYCLE(io->clk);
    cmd >>= 1;
  }

  // Read 8 bytes LSB-first
  pin_mode(io->data, INPUT);
  uint8_t regs[8] = {0};

  for (int i = 0; i < 8; i++) {
    uint8_t data = 0;
    for (int bit = 0; bit < 8; bit++) {
      CLK_CYCLE(io->clk);
      data |= (pin_read(io->data) << bit);
    }
    regs[i] = data;
  }

  pin_low(io->ce);

  dst->sec   = bcd2dec(regs[0]);
  dst->min   = bcd2dec(regs[1]);
  dst->hour  = bcd2dec(regs[2] & 0x3f); // mask out 12/24
  dst->date  = bcd2dec(regs[3]);
  dst->month = bcd2dec(regs[4]);
  dst->day   = bcd2dec(regs[5]);
  dst->year  = bcd2dec(regs[6]);
}

void rtc_set_datetime(spi_t *io, rtc_datetime_t *dt) {
  rtc_write(io, WriteSecond, dec2bcd(dt->sec));   // Seconds (CH=0)
  rtc_write(io, WriteMinute, dec2bcd(dt->min));   // Minutes
  rtc_write(io, WriteHour,   dec2bcd(dt->hour));  // Hours (12:00, 24h mode)
  rtc_write(io, WriteDate,   dec2bcd(dt->date));   // Date: 1st
  rtc_write(io, WriteMonth,  dec2bcd(dt->month));   // Month: April
  rtc_write(io, WriteDay,    dec2bcd(dt->day));   // Day of week: Tuesday
  rtc_write(io, WriteYear,   dec2bcd(dt->year));
}

uint8_t dec2bcd(uint8_t dec) {
  return ((dec / 10) << 4) | (dec % 10);
}

uint8_t bcd2dec(uint8_t bcd) {
  uint8_t ones = bcd & 0x0f;
  uint8_t tens = bcd >> 4;
  return tens * 10 + ones;
}
