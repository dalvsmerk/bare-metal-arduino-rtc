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
      DDRB &= ~(1 << (pin - 8));
    } else {
      DDRB |= (1 << (pin - 8));
    }
  }
}

/**
  * @param pin [0; 13] arduino nano digital pins
  * @param value 0 or 1
  */
void pin_write(int pin, logic_level_t level) {
  if (pin < 8) {
    if (level) {
      PORTD |= (1 << pin);
    } else {
      PORTD &= ~(1 << pin);
    }
  } else {
    if (level) {
      PORTB |= (1 << (pin - 8));
    } else {
      PORTB &= ~(1 << (pin - 8));
    }
  }
}

inline void pin_high(int pin) {
  pin_write(pin, HIGH);
}

inline void pin_low(int pin) {
  pin_write(pin, LOW);
}

uint8_t pin_read(int pin) {
  if (pin < 8) {
    return PIND & (1 << pin);
  } else {
    return PINB & (1 << (pin - 8));
  }
}
