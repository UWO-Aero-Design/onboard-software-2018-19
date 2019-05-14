#ifndef ETV4_H
#define ETV4_H

#include <Arduino.h>
#include <stdint.h>
#include "GPS.h"

class GPS_ETV4: public GPS{
  public:

    float latitude, longitude, MSLAlt;
    float Speed, course;
    float HDOP, VDOP, PDOP;
    char NSInd, EWInd, mode1;
    uint8_t fix, satellites, mode2;
    float Time, geoSep;
    
    void init();
    void update();
    
  private:
    char data[256];
    uint8_t pos;
    
    void readGPGGA(char *data);
    void readGPRMC(char *data);
    void readGPGSA(char *data);
};

#endif
