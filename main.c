// automeas-embeded-0-0-0 by Kczyz
/*
    Project :
        AUTOMEAS
    Description:
        A simple program that establishes comms  between
        PC and MCU.
*/

#include "includes_definitions.h"
#include "rx.h"
#include "tx.h"
int main(void) {
  UBRR0H = (BRC >> 8);
  UBRR0L = BRC;
  UCSR0B = (1 << TXEN0) | (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  DDRB = (1 << PORTB1);
  sei();
  serialWrite("Hello\n\r");
  serialWrite("World\n\r");
  _delay_ms(1500);
  serialWrite("Goodbye\n\r");
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
ISR(USART_TX_vect) {
  if (txReadPos != txWritePos) {
    UDR0 = txBuffer[txReadPos++];
    if (txReadPos >= TX_BUFFER_SIZE) {
      txReadPos++;
    }
  }
}