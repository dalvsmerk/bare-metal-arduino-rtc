#define F_CPU 16000000UL
#define BAUD 9600UL

#include "uart.h"

int main(void) {
  uart_init();
  uart_tx('h');
  uart_tx('e');
  uart_tx('l');
  uart_tx('l');
  uart_tx('o');

  return 0;
}
