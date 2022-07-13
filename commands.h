// by Kczyz
/*
    code responsible for translating States into pins
*/
#ifndef COMMANDS_H
#define COMMANDS_H
//
#include <stdint.h>
#include <avr/io.h>
#define SDIR_LEFT 0
#define SDIR_RIGHT 1
#define INIT_DRIVER_STATE(X)                                                   \
  DriverState X = {.mode = sleep, .dir = right, .val = 0}
typedef enum {
  error,
  same,
  sleep,
  full,
  half_type_a,
  quarter,
  half_type_b,
  one_8,
  one_16,
  one_32
} StepMode;
typedef enum {
    left,
    right
} LogicState;
typedef struct {
  StepMode mode;
  LogicState dir;
  uint8_t val;
} DriverState;
void SetState(DriverState T) {
  uint8_t val = PORTB;
  static StepMode previousMode;
  { // set mode
    if (T.mode == same || T.mode == previousMode){
      // do nothing
    } else {
      val = (T.mode - 2 << 2); // to be explained
    }
    }
    { // set dir
        if(T.dir == right){
          val |= (1 << 1);
        }
        else if(T.dir == left){
            val &= ~(1 << 1);
        }
    }
    { // set val
            // flip switch T.val times
    }
    previousMode = T.mode;
}
#endif