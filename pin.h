/**
  * Map between digital pin number and corresponding mega328p register
  *
  * digital - simplification for the sake of excercise, can be analog as well
  */
#pragma once

#include "int.h"

typedef enum pin_mode {
  INPUT = 0,
  OUTPUT = 1
} pin_mode_t;

typedef enum logic_level {
  LOW = 0,
  HIGH = 1
} logic_level_t;

// pin should be unsigned but whatever
void    pin_mode(int pin, pin_mode_t mode);
void    pin_write(int pin, logic_level_t value);
void    pin_high(int pin);
void    pin_low(int pin);
uint8_t pin_read(int pin);
