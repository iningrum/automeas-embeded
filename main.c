// automeas-embeded-0-0-0 by Kczyz
/*
    Project :
        AUTOMEAS
    Description:
        A simple program that establishes comms  between
        PC and MCU.
*/
#include <avr/interrupt.h>
#include <avr/io.h>
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define F_CPU 16000000
#define BAUD 9600
#define BRC ((F_CPU / 16 / BAUD) - 1)
#define RX_BUFFER_SIZE 128
char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChr(void) {
  char ret = '\0';
  if (rxReadPos != rxWritePos) {
    ret = rxBuffer[rxReadPos++];
    if (rxReadPos >= RX_BUFFER_SIZE) {
      rxReadPos = 0;
    }
  }
  return ret;
}
char peekChr(void) {
  char ret = '\0';
  if (rxReadPos != rxWritePos) {
    ret = rxBuffer[rxReadPos];
  }
  return ret;
}
int main(void) {
  UBRR0H = (BRC >> 8);
  UBRR0L = BRC;
  UCSR0B = (1 << RXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  DDRB = (1 << PORTB1);
  sei();
  while (1) {
    char c = getChr();
    if (c == '1') {
      sbi(PORTB, PORTB1);
    } else if (c == '0') {
      cbi(PORTB, PORTB1);
    }
  }
}
ISR(USART_RX_vect) {
  rxBuffer[rxWritePos++] = UDR0;
  if (rxWritePos >= RX_BUFFER_SIZE) {
    rxWritePos = 0;
  }
}