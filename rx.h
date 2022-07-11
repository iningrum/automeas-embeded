// by Kczyz
/*
    Code responsible for handling incoming usart transmisions
*/
#ifndef RX_H
#define RX_H
#include "main.h"
// functions
char getChr(void) {
  char ret = '\0';
  if (rx.ReadPos != rx.WritePos) {
    ret = rx.Buffer[rx.ReadPos++];
    if (rx.ReadPos >= BUFFER_SIZE) {
      rx.ReadPos = 0;
    }
  }
  return ret;
}
char lpeekChr(void) {
  char ret = '\0';
  if (rx.ReadPos != rx.WritePos) {
    ret = rx.Buffer[rx.WritePos - 1];
    if (rx.ReadPos >= BUFFER_SIZE) {
      rx.ReadPos = 0;
    }
  }
  return ret;
}
#endif