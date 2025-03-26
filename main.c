#define F_CPU 16000000UL
#define BAUD 9600UL

#include "avr/io.h"
#include "logger.h"
#include "uart.h"
#include "rtc.h"
#include "pin.h"

logger_t logger = {
  .init = uart_init,
  .debug = uart_txs,
  .debug_byte = uart_tx
};

#define CLK 12
#define DATA 11
#define CE 10

void dec2str(uint8_t year, char* dest, int len);

int main(void) {
  logger.init();

  // debug led - to be removed
  pin_mode(13, OUTPUT);
  pin_high(13);

  spi_t rtc_io = {
    .clk = CLK, 
    .data = DATA, 
    .ce = CE
  };

  rtc_init(&rtc_io);
  uint8_t year = rtc_read_year(&rtc_io);
  logger.debug_byte(year);
  // char year_str[2];
  // dec2str(year, year_str, 2);
  // logger.debug(year_str);
  logger.debug("\n");

  while (1)
    ;

  // unreachable
}

void dec2str(uint8_t dec, char* dst, int len) {
  for (int i = 0; i < len; i++) {
    dst[i] = '0' + dec % 10; // int arithmetics
    dec /= 10;
  }
}
