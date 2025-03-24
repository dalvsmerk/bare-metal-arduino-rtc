# Demo: Bare-metal programming of Arduino

## Prerequisites

- Arduino UNO board
- USB Type-A to USB Type-B adapter

## Setup

MacOS:

1. Install dependencies
```shell
brew install avr-gcc avrdude
```
2. Connect your Arduino board to computer via USB cable.
3. Run `ls /dev/tty.usb*` to get the serial port name and save it to `.env`.
```shell
echo "PORT=$(ls /dev/tty.usb*)" > .env
```

## Execute

1. Run `make flash` to compile the demo program and write it to on-board flash storage.
2. Confirm that the on-board LED-light blinks.
3. ???
4. Profit
