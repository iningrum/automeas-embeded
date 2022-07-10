#ifndef DATUM_H
#define DATUM_H
#include "includes_definitions.h"
typedef struct {
  char cmd;
  uint8_t val;
} Datum;
Datum void getDatum(char c[]); // translates str like "c1234" to Datum

#endif