C = avr-gcc
LDFLAGS ?= -mmcu=atmega328p 
CFLAGS ?= -Os -DF_APU=16000000UL $(LDFLAGS)
PORT ?= /dev/ttyUSB0


all: comm.hex
comm.hex: comm
	avr-objcopy -O ihex -R .eeprom comm comm.hex
comm: comm.o
	avr-gcc $(LDFLAGS) -o  $@ $^
comm.o: main.c
	avr-gcc $(CFLAGS) -c -o $@ $<


deploy: comm.hex
	avrdude -F -V -c arduino  -p atmega328p -P $(PORT) -b 115200 -U flash:w:comm.hex

clean:
	rm *.hex
	rm *.o
	rm comm
