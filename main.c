#define F_CPU 16000000UL
#define BAUD 9600UL

#include "avr/io.h"
#include "logger.h"
#include "uart.h"
#include "spi.h"
#include "pin.h"

logger_t logger = {
  .init = uart_init,
  .debug = uart_txs,
};

#define CLK 12
#define DATA 11
#define CE 10

int main(void) {
  logger.init();
  logger.debug("test\n");

  // DDRB |= (1 << PB5);
  // PORTB &= ~(1 << PB5);

  spi_t spi_io = {
    .clk = CLK, 
    .data = DATA, 
    .ce = CE
  };

  spi_init(&spi_io);

  while (1)
    ;

  // unreachable
}
