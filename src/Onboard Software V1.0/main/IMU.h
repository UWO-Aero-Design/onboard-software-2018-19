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
    ~IMU();
    virtual void initIMU(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg) = 0;
    virtual void updateSensor() = 0;
    virtual void printYPR() = 0;
    float getYaw();
    float getPitch();
    float getRoll();
  protected:
    float yaw;
    float pitch;
    float roll;

};

#endif
