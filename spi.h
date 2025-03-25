/*
 * 3-Wire serial interface
 */
#pragma once

#include "avr/io.h"

typedef struct spi_t {
  int clk;
  int data;
  int ce;
} spi_t;

void    spi_init(spi_t *io);
uint8_t spi_read(spi_t *io);
void    spi_write(spi_t *io, uint8_t data);

void shift_byte(int pin, uint8_t data);
