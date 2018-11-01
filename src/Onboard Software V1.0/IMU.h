#ifndef IMU_h
#define IMU_h

#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class IMU {
  public: 
    IMU();
    float getYaw();
    float getPitch();
    float getRoll();
    virtual void init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg);
    virtual void update();
    void printYPR();

};

#endif
