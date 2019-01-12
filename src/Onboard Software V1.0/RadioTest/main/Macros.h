#ifndef MACROS_H
#define MACROS_H

/*
 * Author: Carl Baron - Nov 2018
 * File Purpose
 *    The purpose of this file is to define macros
 */

/***** Bit operation macros *****/
// Return x as either 1 or 0, depending on the bit in 'x' at position 'y'
#define READ(x,y) ((0u == (x & (1<<y)))?0u:1u)

// Return x with bit y set to 1
#define SET(x,y) x |= (1 << y)

// Return x with bit y set to 0
#define CLEAR(x,y) x &= ~(1<< y)

// Return x with bit y inverted meaning if the bit was 1, it will be 0 and if it was 0, it will be 1
#define TOGGLE(x,y) (x ^= (1<<y))

// TODO: Macros for turning ON/OFF a certain port
// Make lookup table for Teensy Ports (If needed?)

#endif // MACROS_H