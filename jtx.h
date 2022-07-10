// automeas-embeded-0.0.0 by Kczyz
/*
    Code responsible for transmiting data over USART
*/
#ifndef TX_H
#define TX_H
#include "includes_definitions.h"
// variables
char txBuffer[TX_BUFFER_SIZE];
uint8_t txReadPos = 0;
uint8_t txWritePos = 0;
// functions
void appendSerial(char c) {
  txBuffer[txWritePos++] = c;
  if (txWritePos >= TX_BUFFER_SIZE) {
    txWritePos = 0;
  }
}
void serialWrite(char c[]) {
  for (uint8_t i = 0; i < strlen(c); i++) {
    appendSerial(c[i]);
  }
  if (UCSR0A & (1 << UDRE0)) {
    UDR0 = 0;
  }
}
#endif