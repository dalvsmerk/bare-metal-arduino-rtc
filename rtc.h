/*
 * RTC DS1302
 */
#pragma once

#include "avr/io.h"

#define DELAY_US 1 // reconsider shorter delay if possible (using baud rate)

#define CLK_CYCLE(clk_pin) \
  do {                     \
    pin_high(clk_pin);     \
    _delay_us(DELAY_US);   \
    pin_low(clk_pin);      \
    _delay_us(DELAY_US);   \
  } while(0)

typedef struct spi_t {
  int clk;
  int data;
  int ce;
} spi_t;

typedef enum rtc_cmd_t {
  ReadSecond        = 0x81,
  ReadMinute        = 0x83,
  ReadHour          = 0x85,
  ReadDate          = 0x87,
  ReadMonth         = 0x89,
  ReadDay           = 0x8b,
  ReadYear          = 0x8d,
  ReadWriteProtect  = 0x8f,
  ReadBurstClock    = 0xbf,
  WriteSecond       = 0x80,
  WriteMinute       = 0x82,
  WriteHour         = 0x84,
  WriteDate         = 0x86,
  WriteMonth        = 0x88,
  WriteDay          = 0x8a,
  WriteYear         = 0x8c,
  WriteWriteProtect = 0x8e
} rtc_cmd_t;

typedef struct rtc_datetime_t {
  int sec;
  int min;
  int hour;
  int day;
  int date;
  int month;
  int year;
} rtc_datetime_t;

void    rtc_init(spi_t *io);
uint8_t rtc_read(spi_t *io, rtc_cmd_t cmd);
void    rtc_burst_read(spi_t *io, rtc_datetime_t *dst);
void    rtc_write(spi_t *io, rtc_cmd_t cmd, uint8_t data);

void rtc_set_datetime(spi_t *io, rtc_datetime_t *datetime);

uint8_t dec2bcd(uint8_t dec);
uint8_t bcd2dec(uint8_t bcd);
