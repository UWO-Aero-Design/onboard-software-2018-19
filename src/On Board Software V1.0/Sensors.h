#ifndef SENSORS_H
#define SENSORS_H

#include "Config.h"
class Sensors{
  private:
  	IMU imu;
  	Barometer barometer;
  	GPS gps;
  public:
  	Sensors();
  	void init(systemType sysTyp);
  	virtual void read() = 0;
};

#endif // SENSORS_H
