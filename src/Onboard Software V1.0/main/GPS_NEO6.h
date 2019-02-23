#ifndef ETV4_H
#define ETV4_H

#include <Arduino.h>
#include <stdint.h>
#include "GPS.h"

class GPS_NEO6: public GPS{
  public:
    GPS_NEO6();
    ~GPS_NEO6();
  
    void init();
    void update();
    
    //getters for ETV4 specific data
    double getLat();
    double getLon();
    double getAlt();
    uint8_t getDay();
    uint8_t getMonth();
    uint16_t getYear();
    uint8_t getHour();
    uint8_t getMin();
    uint8_t getSec();
    double getSpeed();
    double getCourse();
    float getHdop();
    uint32_t getSatellites();

  protected:
    //NEMA values
    uint8_t day, month; 
    uint16_t year; 
    uint8_t hour, min, sec; 
    double speed, course; 
    float hdop; 
    uint32_t satellites;
};

#endif
