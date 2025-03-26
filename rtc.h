/*
 * RTC DS1302
 */
#pragma once

#include "avr/io.h"

typedef struct spi_t {
  int clk;
  int data;
  int ce;
} spi_t;

typedef enum rtc_cmd_read_t {
  SEC_R  = 0x81,
  MIN_R  = 0x83,
  HOUR_R = 0x85,
  DATE_R = 0x87,
  MON_R  = 0x89,
  DAY_R  = 0x8b,
  YEAR_R = 0x8d
} rtc_cmd_read_t;

typedef enum rtc_cmd_write_t {
  SEC_W  = 0x80,
  MIN_W  = 0x82,
  HOUR_W = 0x84,
  DATE_W = 0x86,
  MON_W  = 0x88,
  DAY_W  = 0x8a,
  YEAR_W = 0x8c
} rtc_cmd_write_t;

void    rtc_init(spi_t *io);
uint8_t rtc_read(spi_t *io, rtc_cmd_read_t cmd);
void    rtc_write(spi_t *io, rtc_cmd_write_t cmd, uint8_t data);

uint8_t rtc_read_year(spi_t *io);
