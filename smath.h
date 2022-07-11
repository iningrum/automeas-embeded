// by Kczyz
/*
  Simple Math - useful but extremely specific functions 
*/
#ifndef SMATH_H
#define SMATH_H
#include <string.h>
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