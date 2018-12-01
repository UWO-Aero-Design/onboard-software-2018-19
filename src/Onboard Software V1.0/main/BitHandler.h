//
// Created by cbaro on 2018-12-01.
//

#ifndef PARSETEST_BITHANDLER_H
#define PARSETEST_BITHANDLER_H

//Set bit y (0-indexed) of x to '0' by generating a mask with a '0' in the y position and 1's elsewhere then ANDing the mask with x.
#include <stdint.h>

#define CLEAR(x,y) x &= ~(1<< y)


//Toggle bit y (0-index) of x to the inverse: '0' becomes '1', '1' becomes '0' by XORing x with a bitmask where the bit in position y is '1' and all others are '0'.
#define TOGGLE(x,y) (x ^= (1<<y))

//Set bit y (0-indexed) of x to '1' by generating a a mask with a '1' in the proper bit location and ORing x with the mask.
#define SET(x,y) x |= (1 << y)

//Return '1' if the bit value at position y within x is '1' and '0' if it's 0 by ANDing x with a bit mask where the bit in y's position is '1' and '0' elsewhere and comparing it to all 0's.  Returns '1' in least significant bit position if the value of the bit is '1', '0' if it was '0'.
#define READ(x,y) ((0u == (x & (1<<y)))?0u:1u)

class BitHandler{
private:
protected:
public:
    uint16_t readBit(uint16_t data, uint8_t bitpos){ return READ(data,bitpos); }

    uint16_t setBit(uint16_t data, uint8_t bitpos){ return SET(data,bitpos); }

    uint16_t toggleBit(uint16_t data, uint8_t bitpos){ return TOGGLE(data,bitpos); }

    uint16_t clearBit(uint16_t data, uint8_t bitpos){ return CLEAR(data,bitpos); }

    // For debugging outside arduino environment
//    void printBufHex(char *buf, int len) {
//        int i;
//
//        for (i = 0; i < len; i++) {
//            printf("%02x ", buf[i] & 0xFF);
//            if (i == (len) - 1) { printf("\n"); }
//        }
//    }

};


#endif //PARSETEST_BITHANDLER_H
