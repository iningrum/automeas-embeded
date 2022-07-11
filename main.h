#ifndef MAIN_H
#define MAIN_H
#include "includes_definitions.h"
// buffer
#define BUFFER_SIZE 128
#define INIT_BUFFER(X) Buffer X = {.WritePos = 0, .ReadPos = 0}
typedef struct {
  char Buffer[BUFFER_SIZE];
  uint8_t WritePos;
  uint8_t ReadPos;
} Buffer;
INIT_BUFFER(rx); // receive data
INIT_BUFFER(tx); // transmit data
char echoBuffer[2] = {'\0', '\0'};
char *echoVal = &echoBuffer[0];
#endif