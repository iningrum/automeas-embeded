// by Kczyz
/*
    Contains all includes and macros
    used all over the project.
*/
#ifndef INCLUDES_AND_DEFINITIONS_H
#define INCLUDES_AND_DEFINITIONS_H
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#define F_CPU 16000000 // CPU frequency
#include <util/delay.h>
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clears i-th bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))  // sets i-th bit
#define BAUD 9600                                   // baudrate
#define BRC ((F_CPU / 16 / BAUD) - 1)               // ??
// greeter definitions
#define GREETER_LINE1 "automeas-embeded-0.1.0 by Kczyz\n\r"
#define GREETER_LINE2 "-------------------------------\n\r"
#endif