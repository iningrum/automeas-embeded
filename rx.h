// automeas-embeded-0.0.0 by Kczyz
/*
    Code responsible for handling incoming usart transmisions
*/
#ifndef RX_H
#define RX_H
#include "includes_definitions.h"
// variables
char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;
// functions
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
#endif