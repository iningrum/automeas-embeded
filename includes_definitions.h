// automeas-embeded-0.0.0 by Kczyz
/*
    Contains all includes and macros
    used all over the project.
*/
#ifndef INCLUDES_AND_DEFINITIONS_H
#define INCLUDES_AND_DEFINITIONS_H
#include <avr/interrupt.h>
#include <avr/io.h>
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clears i-th bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))  // sets i-th bit
#define F_CPU 16000000                              // CPU frequency
#define BAUD 9600                                   // baudrate
#define BRC ((F_CPU / 16 / BAUD) - 1)               // ??
#define RX_BUFFER_SIZE 128                          // receive buffer
#endif