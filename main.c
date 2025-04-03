#define F_CPU 16000000UL
#define BAUD 9600UL

#include "avr/io.h"
#include "util/delay.h"
#include "logger.h"
#include "uart.h"
#include "rtc.h"
#include "pin.h"

logger_t logger = {
  .init = uart_init,
  .debug = uart_txs,
  .debug_byte = uart_tx
};

#define LED 13

#define SCLK 12
#define DATA 11
#define CE 10

void dec2str(uint8_t year, char* dest, int len);

void rtc_debug_burst(spi_t *io);
void rtc_set_time_default(spi_t *io);

int main(void) {
  logger.init();

  spi_t rtc_io = {
    .sclk = SCLK, 
    .data = DATA, 
    .ce = CE
  };

  rtc_init(&rtc_io);

  // uint8_t sec = rtc_read(&rtc_io, ReadSecond);
  // rtc_write(&rtc_io, WriteSecond, sec & 0x7f);

  // uint8_t ctrl = rtc_read(&rtc_io, 0x8F);
  // logger.debug_byte(ctrl);  // should not be 0x00 unless write-protect is set

  // rtc_datetime_t dt = {
  //   .sec = 1,
  //   .min = 2,
  //   .hour = 21,
  //   .day = 3,
  //   .date = 2,
  //   .month = 4,
  //   .year = 12
  // };

  // rtc_set_datetime(&rtc_io, &dt);

  // rtc_burst_read(&rtc_io, &dt);
  // logger.debug_byte(bcd2dec(dt.sec));
  // logger.debug_byte(bcd2dec(dt.min));
  // logger.debug_byte(bcd2dec(dt.hour & 0x3f));
  // logger.debug_byte(bcd2dec(dt.year));

  while (1) {
    logger.debug_byte(bcd2dec(rtc_read(&rtc_io, ReadSecond) & 0x7f));
    _delay_ms(1000);
  }

  while (1)
    ;

  // unreachable
}

void dec2str(uint8_t dec, char* dst, int len) {
  for (int i = len - 1; i > -1; i--) {
    dst[i] = '0' + dec % 10; // int arithmetics
    dec /= 10;
  }
}
