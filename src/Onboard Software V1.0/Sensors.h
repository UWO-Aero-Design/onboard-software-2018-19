#ifndef SENSORS_H
#define SENSORS_H

#include "Config.h"
#include "dataStructs.h"
class Sensors{
  private:
  	IMU imu;
  	Barometer barometer;
  	GPS gps;
  	SystemType sysTyp;
    SensorData sensorData;

  public:
  	Sensors();
    
  	void init(systemType sysTyp);
    void read();

  	uint8_t* getPacket();
  	int getPacketSize();

  	
};

#endif // SENSORS_H
