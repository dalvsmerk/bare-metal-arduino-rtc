#define F_CPU 16000000UL
#define BAUD 9600UL

#include "avr/io.h"
#include "logger.h"
#include "uart.h"
#include "spi.h"

logger_t logger = {
  .init = uart_init,
  .debug = uart_txs,
};

int main(void) {
  logger.init();
  logger.debug("test\n");

  // DDRB |= (1 << PB5);
  // PORTB &= ~(1 << PB5);

  spi_t spi_io = {
    .clk = 12, 
    .data = 11, 
    .ce = 10 
  };

  spi_init(&spi_io);

  while (1)
    ;

  // unreachable
}
