#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

/*
 * Author: Carl Baron - Nov 2018
 * File Purpose
 *    The purpose of this file is to define simple to use bit operations
 */
#include "Arduino.h"
#include "Macros.h"

namespace bit{ 
  /**
  READ macro wrapper to return the value of a certain bit in a unsigned integer
  @param[in]  uint16_t data, the variable to check a specific bit of
  @param[in]  uint8_t bitpos, the bit position to check in the variable. 0 is LSB    
  @return     uint16_t, value that is 0 if bit at bitpos in data is 0, and 1 if bit at bitpos is 1
  */
  uint16_t readBit(uint16_t data, uint8_t bitpos)
  { 
      return READ(data, bitpos); 
  }

  /**
  SET macro wrapper to return the value of an unsigned integer after setting a bit in the value to 1
  @param[in]  uint16_t data, the variable to set a specific bit of
  @param[in]  uint8_t bitpos, the bit position of the bit to set in data. 0 is LSB    
  @return     uint16_t, value that is equal to data except that bit at bitpos is set to 1
  */
  uint16_t setBit(uint16_t data, uint8_t bitpos)
  { 
      return SET(data, bitpos);
  }

  /**
  CLEAR macro wrapper to return the value of an unsigned integer after clearing a bit in the value, setting it to 0
  @param[in]  uint16_t data, the variable to clear a specific bit of
  @param[in]  uint8_t bitpos, the bit position of the bit to clear in data. 0 is LSB    
  @return     uint16_t, value that is equal to data except that bit at bitpos is set to 0
  */
  uint16_t clearBit(uint16_t data, uint8_t bitpos)
  { 
      return CLEAR(data, bitpos); 
  }

  /*
  TOGGLE macro wrapper to return the value of an unsigned integer after inverting a bit in a variable
  @param[in]  uint16_t data, the variable to toggle a specific bit of
  @param[in]  uint8_t bitpos, the bit position of the bit to be toggled in data. 0 is LSB    
  @return     uint16_t, value that is equal to data except that bit at bitpos is toggled meaning that if that bit was 0, it is now 1. And vice versa
  */
  uint16_t toggleBit(uint16_t data, uint8_t bitpos)
  { 
      return TOGGLE(data, bitpos); 
  }

  // Swap order of bytes in 16 bit unsigned variable
  uint16_t swapUINT16(uint16_t val)
  { 
      return (val << 8) | (val >> 8 ); 
  }

  // Swap order of bytes in 16 bit signed variable
  int16_t swapINT16(int16_t val)
  { 
      return (val << 8) | ((val >> 8) & 0xFF); 
  }

  // Swap order of bytes in 32 bit unsigned variable
  uint32_t swapUINT32(uint32_t val) 
  {
      val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
      return (val << 16) | (val >> 16);
  }

  // Swap order of bytes in 32 bit signed variable
  int32_t swapINT32(int32_t val) 
  {
      val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
      return (val << 16) | ((val >> 16) & 0xFFFF);
  }

  // Swap order of bytes in 64 bit unsigned variable
  uint64_t swapUINT64(uint64_t val)
  {
      val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
      val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
      return (val << 32) | (val >> 32);
  }

  // Swap order of bytes in 64 bit signed variable
  int64_t swapINT64(int64_t val)
  {
      val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
      val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
      return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
  }

  // Used for debugging by allowing us to print a hex string based on an input char* buffer
  void printHex(char *buf, int len) 
  {
      for (int i = 0; i < len; i++) {
          Serial.println(buf[i] & 0xFF, HEX);
          if (i == (len) - 1) { Serial.println(""); }
      }
  }
}

#endif // BIT_MANIPULATION_H