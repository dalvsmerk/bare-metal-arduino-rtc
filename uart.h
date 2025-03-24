/**
  * Copy pasted from https://github.com/dalvsmerk/bare-metal-arduino-usart/blob/b48ae5d50999fefb43572f4a97190a2751c45e8f/uart.h
  */
#pragma once

#ifndef F_CPU
 #error F_CPU on-entry value is required
#endif

#ifndef BAUD
 #error BAUD on-entry value is required
#endif

#include "avr/io.h"
#include <util/setbaud.h>

#define uint8_t unsigned char

#define UFRAME_8BIT 0x06 // 0b0110

void    uart_init(void);
void    uart_tx(uint8_t data);
void    uart_txs(char* data);
uint8_t uart_rx(void);

inline void uart_init(void) {
  // set baud rate
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  // set frame format
  UCSR0C = UFRAME_8BIT;

  // enable transmitter and receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

inline void uart_tx(uint8_t data) {
  // wait until data register is empty
  while (!(UCSR0A & (1 << UDRE0)))
    ;

  // write data to tx buffer
  UDR0 = data;
}

inline uint8_t uart_rx(void) {
  while (!(UCSR0A & (1 << RXC0)))
    ;

  return UDR0;
}

/**
  * @param data null-terminated string
  */
void uart_txs(char* data) {
  while (*data != '\0')
    uart_tx(*(data++));
}
