// by Kczyz
/*
    Code responsible for transmiting data over USART
*/
#ifndef TX_H
#define TX_H
#include <string.h>
// variables
// functions
void appendSerial(char c) {
  tx.Buffer[tx.WritePos++] = c;
  if (tx.WritePos >= BUFFER_SIZE) {
    tx.WritePos = 0;
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