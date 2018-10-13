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
    void setupInterruptHandler(uint8_t intPin, void (*interruptAction)(void), int value);
    void dmpDataReady(void);
    uint8_t getYaw();
    uint8_t getPitch();
    uint8_t getRoll();
    void init();
    void update();


  private:
};

#endif
