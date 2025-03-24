-include .env

MCU 	 = atmega328p
F_CPU  = 16000000UL

CC 		 = avr-gcc
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
OBJ 	 = main.o
TARGET = main

all: $(TARGET).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

flash: $(TARGET).hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b 115200 -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex
