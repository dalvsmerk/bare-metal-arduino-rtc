#include "pin.h"
#include "avr/io.h"

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
void pin_set(int pin, logic_level_t level) {
  if (pin < 8) {
    if (level) {
      PORTD |= (1 << pin);
    } else {
      PORTD &= ~(1 << pin);
    }
  } else {
    if (level) {
      PORTB |= (1 << pin);
    } else {
      PORTB &= ~(1 << pin);
    }
  }
}

inline void pin_high(logic_level_t pin) {
  pin_set(pin, HIGH);
}

inline void pin_low(logic_level_t pin) {
  pin_set(pin, LOW);
}
