// by Kczyz
/*
    Project :
        AUTOMEAS
    Description:
        A simple program that establishes comms  between
        PC and MCU.
*/
#define RDEL 300
#define LDEL 300
#include <avr/interrupt.h>
#include <avr/io.h>
#include "includes_definitions.h"
#include "main.h"
#include "rx.h"
#include "tx.h"
#include "smath.h"
typedef struct {
  char cmd;
  uint8_t val;
} Datum;
void clearAllMs(){
  cbi(PORTB, PB4);
  cbi(PORTB, PB3);
  cbi(PORTB, PB2);
}
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
      switch(T.cmd){
        case 'f':
          clearAllMs();
          sbi(PORTB, PB2);
          break;
        case 'h':
          if(T.val==0){
            // kolowe pul kroku a
            clearAllMs();
            sbi(PORTB, PB3);
          } else {
            // kolowe pol kroku b
            clearAllMs();
            sbi(PORTB, PB4);
          }
          break;
        case '4':
          cbi(PORTB, PB4);
          sbi(PORTB, PB3);
          sbi(PORTB, PB2);
          break;
        case '8':
          sbi(PORTB, PB4);
          cbi(PORTB, PB3);
          sbi(PORTB, PB2);
          break;
        case '6':
          sbi(PORTB, PB4);
          sbi(PORTB, PB3);
          cbi(PORTB, PB2);
          break;
        case '3':
          sbi(PORTB, PB4);
          sbi(PORTB, PB3);
          sbi(PORTB, PB2);
          break;
        case 'l':
          cbi(PORTB, PB1);
          for (uint8_t i = 0; i <= T.val; i++){
            sbi(PORTB, PB0);
            _delay_ms(LDEL);
            cbi(PORTB, PB0);
            _delay_ms(RDEL);
          }
            break;
        case 'r':
          sbi(PORTB, PB1);
          for (uint8_t i = 0; i <= T.val; i++){
            sbi(PORTB, PB0);
            _delay_ms(LDEL);
            cbi(PORTB, PB0);
            _delay_ms(RDEL);
          }
          break;
        case 'p':
          clearAllMs();
          break;
        }
    }
  }
}
ISR(USART_RX_vect) {
  rx.Buffer[rx.WritePos++] = UDR0;
  if (rx.WritePos >= BUFFER_SIZE) {
    rx.WritePos = 0;
  }
}
ISR(USART_TX_vect) {
  if (tx.ReadPos != tx.WritePos) {
    UDR0 = tx.Buffer[tx.ReadPos++];
    if (tx.ReadPos >= BUFFER_SIZE) {
      tx.ReadPos++;
    }
  }
}