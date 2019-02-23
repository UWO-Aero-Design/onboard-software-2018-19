/*
 * File Purpose
 *   Implementing TestSystem.h functions
 */

// For delay and serial
#include "Arduino.h"
#include "CompSystem.h"
#include "Config.h"
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
  imu = factory->selectIMU(MPU6050);
  baro = factory->selectBaro(BMP085);
  gps = factory->selectGPS(0);
  sd = factory->selectSD(0);
  
  imu->init(imuOffset[0], imuOffset[1], imuOffset[2], imuOffset[3], imuOffset[4], imuOffset[5]);
  baro->init();
  gps->init();
  sd->init();
}

void CompSystem::updateSystem()
{

  imu->update();
  baro->update();
  gps->update();


  if(!plotter) Serial.print("(YPR, Temp)\t");
  Serial.print(imu->getYaw());
  Serial.print(" ");
  Serial.print(imu->getPitch());
  Serial.print(" ");
  Serial.print(imu->getRoll());
  Serial.print(" ");
  if(!plotter) Serial.print(baro->getTemperature());
  Serial.println();
  
}
