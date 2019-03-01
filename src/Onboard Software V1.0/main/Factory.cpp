/*
 * File Purpose
 *    Implementing Factory.h functions
 */

#include "Factory.h"

// Initializing static class variables
uint8_t Factory::IMUInstances = 0;
uint8_t Factory::baroInstances = 0;
uint8_t Factory::GPSInstances = 0;
uint8_t Factory::SDInstances = 0;
uint8_t Factory::SBInstances = 0;

// Default constructor
Factory::Factory(){}

Factory::~Factory(){}

// Return the number of test objects that have been created. 
uint8_t Factory::getIMUInstances() {
	return IMUInstances;
}

uint8_t Factory::getBaroInstances() {
  return baroInstances;
}

uint8_t Factory::getGPSInstances() {
  return GPSInstances;
}

uint8_t Factory::getSDInstances() {
  return GPSInstances;
}

uint8_t Factory::getSBInstances() {
  return GPSInstances;
}

IMU_MPU6050* Factory::selectIMU(uint8_t imu) {
	// Returned object
	IMU_MPU6050* object;

	// Checking what model to create
	switch(imu)
	{
		default:
		{
			object = new IMU_MPU6050();
      ++IMUInstances;
			break;
		}
	}
	return object;
}


Barometer* Factory::selectBaro(uint8_t baro) {
  // Returned object
  Barometer* object;

  // Checking what model to create
  switch(baro)
  {
    default:
    {
      object = new Barometer();
      ++baroInstances;
      break;
    }
  }
  return object;
}

GPS* Factory::selectGPS(uint8_t gps) {
  // Returned object
  GPS* object;

  // Checking what model to create
  switch(gps)
  {
    default:
    {
      object = new GPS_NEO6();
      ++GPSInstances;
      break;
    }
  }
  return object;
}

SDCardWriter* Factory::selectSD(uint8_t sd) {
  // Returned object
  SDCardWriter* object;

  // Checking what model to create
  switch(sd)
  {
    default:
    {
      object = new SDCardWriter_Teensy();
      ++SDInstances;
      break;
    }
  }
  return object;
}

ServoBoard* Factory::selectSB(uint8_t sb) {
  // Returned object
  ServoBoard* object;

  // Checking what model to create
  switch(sb)
  {
    default:
    {
      object = new ServoBoard();
      ++SBInstances;
      break;
    }
  }
  return object;
}

// Encapsulating LED constructor. Default LED has duration 10000, period 1000, duty 50
LED* Factory::selectLED(uint8_t ledPin)
{
	return new LED(ledPin, 10000, 1000, 50);
}
