// automeas-embeded-0.0.0 by Kczyz
/*
    Code responsible for handling incoming usart transmisions
*/
#ifndef RX_H
#define RX_H
#include "includes_definitions.h"
// variables
char rxBuffer[RX_BUFFER_SIZE];
char echoBuffer[2] = {'\0', '\0'};
char *echoVal = &echoBuffer[0];
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
char lpeekChr(void) {
  char ret = '\0';
  if (rxReadPos != rxWritePos) {
    ret = rxBuffer[rxWritePos - 1];
    if (rxReadPos >= RX_BUFFER_SIZE) {
      rxReadPos = 0;
    }
  }
  return ret;
}
char peekLastChr(void) {
  char ret = '\0';
  if (rxReadPos != rxWritePos && rxWritePos > 0) {
    ret = rxBuffer[rxWritePos - 1];
  }
  return ret;
}
uint8_t dec_pow2(uint8_t b) { // decimal power from 0 to 2
  switch (b) {
  case 0:
    return 1;
    break;
  case 1:
    return 10;
    break;
  case 2:
    return 100;
    break;
  }
}
uint8_t tc28b(char c[]) { // 3 chars to 8bits
  uint8_t val = 0;
  for (uint8_t i = 0; i < 3; i++) {
    switch (c[i]) {
    case '0':
      // nothing happens here
      break;
    case '1':
      val += 1 * dec_pow2(2 - i);
      break;
    case '2':
      val += 2 * dec_pow2(2 - i);
      break;
    case '3':
      val += 3 * dec_pow2(2 - i);
      break;
    case '4':
      val += 4 * dec_pow2(2 - i);
      break;
    case '5':
      val += 5 * dec_pow2(2 - i);
      break;
    case '6':
      val += 6 * dec_pow2(2 - i);
      break;
    case '7':
      val += 7 * dec_pow2(2 - i);
      break;
    case '8':
      val += 8 * dec_pow2(2 - i);
      break;
    case '9':
      val += 9 * dec_pow2(2 - i);
      break;
    }
  }
  return val;
}
#endif