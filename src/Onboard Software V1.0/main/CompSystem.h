#ifndef COMP_SYSTEM_H
#define COMP_SYSTEM_H

/*
 * File Purpose
 *    A simple extension of System.h to test if the System object method is viable
 *    Should use the factory
 */

#include <stdint.h>
#include "System.h"

class CompSystem : public System{
private:
  IMU_MPU6050* imu;
  Barometer* baro;
  GPS* gps;
  SDCardWriter* sd;
  int imuOffset[6] = {-3870, -1297, 632, 75, 50, 14};
  const bool plotter = true;
	
protected:
public:
	CompSystem();
	~CompSystem();

	void initSystem();
	void updateSystem();
};


#endif // TEST_SYSTEM_H
