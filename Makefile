C = avr-gcc
LDFLAGS ?= -mmcu=atmega328p 
CFLAGS ?= -Os -DF_APU=16000000UL $(LDFLAGS)
PORT ?= /dev/ttyACM0


all: comm.hex
comm.hex: comm
	avr-objcopy -O ihex -R .eeprom comm comm.hex
comm: comm.o
	avr-gcc $(LDFLAGS) -o  $@ $^
comm.o: comm.c
	avr-gcc $(CFLAGS) -c -o $@ $<
deploy: led.hex
	avrdude -F -V -c arduino  -p atmega328p -P $(PORT) -b 115200 -U flash:w:led.hex

clean:
	rm *.hex
	rm *.o
	rm comm
