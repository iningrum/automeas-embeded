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
typedef struct {
  char cmd;
  uint8_t val;
} Datum;
Datum getDatum(void) {
  Datum result;
  result.cmd = getChr();
  *echoVal = result.cmd;
  serialWrite(echoBuffer);
  { // get val
    char dataBuffer[3];
    for (uint8_t i = 0; i < 3; i++) {
      dataBuffer[i] = getChr();
      *echoVal = dataBuffer[i];
      serialWrite(echoBuffer);
    }
    serialWrite("\n\r");
    result.val = tc28b(dataBuffer);
    getChr();
  }
  return result;
}
int main(void) {
  Datum T;
  UBRR0H = (BRC >> 8);
  UBRR0L = BRC;
  UCSR0B = (1 << TXEN0) | (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  DDRB = (1 << PORTB1);
  sei();
  serialWrite(GREETER_LINE2);
  serialWrite(GREETER_LINE1);
  serialWrite(GREETER_LINE2);
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  while (1) {
    char c = lpeekChr();
    if (c == 'x') {
      T = getDatum();
      if (T.val == 125 && T.cmd == 'c')
        sbi(PORTB, PORTB2);
      else
        cbi(PORTB, PORTB2);
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