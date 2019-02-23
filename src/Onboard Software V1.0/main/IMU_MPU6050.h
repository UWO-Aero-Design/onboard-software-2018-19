#include "IMU.h"

#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class IMU_MPU6050 : public IMU{
  public: 
    IMU_MPU6050();
    ~IMU_MPU6050();
    float getYaw();
    float getPitch();
    float getRoll();
    void init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg);
    void update();

  protected:
    bool blinkState = false;
    bool dmpReady = false;  // set true if DMP init was successful
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer



};
