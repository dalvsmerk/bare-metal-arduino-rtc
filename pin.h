/**
  * Map between [digital] pin number and corresponding mega328p register
  *
  * [digital] - simplification for the sake of excercise, can be analog as well
  */
#pragma once

enum pin_mode_t {
  INPUT = 0,
  OUTPUT = 1
};

// pin should be unsigned but whatever
void pin_mode(int pin, pin_mode_t mode);
void pin_set(int pin, int value);
void pin_high(int pin);
void pin_low(int pin);

/**
  * @param pin [0; 13] arduino nano digital pins
  * @param mode
  */
void pin_mode(int pin, pin_mode_t mode) {
  if (pin < 8) {
    if (mode == INPUT) {
      DDRD &= ~(1 << pin);
    } else {
      DDRD |= (1 << pin);
    }
  } else {
    if (mode == INPUT) {
      DDRB &= ~(1 << pin);
    } else {
      DDRB |= (1 << pin);
    }
  }
}

/**
  * @param pin [0; 13] arduino nano digital pins
  * @param value 0 or 1
  */
void pin_set(int pin, int value) {
  if (pin < 8) {
    if (value) {
      PORTD |= (1 << pin);
    } else {
      PORTD &= ~(1 << pin);
    }
  } else {
    if (value) {
      PORTB |= (1 << pin);
    } else {
      PORTB &= ~(1 << pin);
    }
  }
}

inline void pin_high(int pin) {
  pin_set(pin, HIGH);
}

inline void pin_low(int pin) {
  pin_set(pin, LOW);
}
