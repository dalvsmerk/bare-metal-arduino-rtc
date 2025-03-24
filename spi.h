/*
 * This module implements 3-Wire serial interface
 */
#pragma once

#define uint8_t char

typedef struct spi_t {
  int pin_clk;
  int pin_data;
  int pin_ce;
} spi_t;

void    spi_init(spi_t config);
uint8_t spi_read(spi_t config);
void    spi_write(uint8_t data);
