#ifndef IMU_MPU6050_h
#define IMU_MPU6050_h

#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class IMU_MPU6050 {
  public: 
    IMU_MPU6050();
    float getYaw();
    float getPitch();
    float getRoll();
    void init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg);
    void update();
    void printYPR();


};

#endif
