#ifndef ONBOARD_SYSTEM_H
#define ONBOARD_SYSTEM_H

/*
 * File Purpose
 *    A simple extension of System.h to test if the System object method is viable
 *    Should use the factory
 */

#include <stdint.h>

#include "SPI.h"
#include "RH_RF95.h"
#include "System.h"

class OnboardSystem : public System{
private:
  IMU_MPU6050* imu;
  Barometer* baro;
  GPS* gps;
  SDCardWriter* sd;

  RH_RF95 *rf95;
	
protected:
public:
	OnboardSystem();
	~OnboardSystem();

	void initSystem();
	void updateSystem();
};


#endif // ONBOARD_SYSTEM_H
