#include "IMU.h"

/*
 * File Purpose
 *    Implements IMU class to work with the MPU6050
 */

#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class IMU_MPU6050 : public IMU{
  public: 
    IMU_MPU6050();
    ~IMU_MPU6050();

    // gets sensor data
    float getYaw();
    float getPitch();
    float getRoll();

    // init with offsets
    void init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg);

    // update sensor
    void update();

    // print for debugging
    void printYPR();


};
