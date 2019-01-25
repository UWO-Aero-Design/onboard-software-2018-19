/*
 * File Purpose
 *   Implementing TestSystem.h functions
 */

// For delay and serial
#include "Arduino.h"

#include "CompSystem.h"
#include "Factory.h"

CompSystem::CompSystem()
{
	factory = new Factory();
}

CompSystem::~CompSystem(){
	// Empty	
}

void CompSystem::initSystem()
{
  imu = factory->selectIMU(0);
  baro = factory->selectBaro(0);
  gps = factory->selectGPS(0);
  sd = factory->selectSD(0);
  
  //imu->init(-3675, -1303, 611, 73, 50, 14);
  baro->init();
  gps->init();
  sd->init();
}

void CompSystem::updateSystem()
{

  //imu->update();
  baro->update();
  gps->update();

  Serial.println(gps->getSatellites());

  
 
	delay(100);
}
