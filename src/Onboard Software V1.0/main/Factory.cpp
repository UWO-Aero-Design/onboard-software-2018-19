#include <stdint.h>

#include "Factory.h"
#include "SDCardWriter.h"
#include "SDCardWriter_Teensy.h"
#include "IMU.h"
#include "IMU_MPU6050.h"

// Initializing static class variables
uint8_t Factory::testInstances = 0;
uint8_t Factory::radioInstances = 0;
uint8_t Factory::sdInstances = 0;
uint8_t Factory::imuInstances = 0;

// Default constructor
Factory::Factory(){}

Factory::~Factory(){}

// Test method for checking if the factory works and compiles
uint8_t Factory::selectTest(uint8_t testModel)
{
	// Returned object
	uint8_t object = 0;

	// Checking what model to create
	switch(testModel){

		default:
		{
			object = 1;
      ++testInstances;
			break;
		}
	}

	return object;
}

SDCardWriter* Factory::selectSD(uint8_t sdModel)
{
  // Returned object
  SDCardWriter *object;

  // Checking what model to create
  switch(sdModel){

    default:
    {
      object = new SDCardWriter_Teensy();
      ++sdInstances;
      break;
    }
  }

  return object;
}

IMU* Factory::selectIMU(uint8_t imuModel)
{
  // Returned object
  IMU *object;

  if(imuInstances == 0) {
  // Checking what model to create
  switch(imuModel){
    default:
    {
      object = new IMU_MPU6050();
      ++imuInstances;
      break;
    }
  }

  return object;

  }
  else {
    // TODO add return object when imuInstances != 0
    return NULL;
  }
}

uint8_t Factory::getTestInstances()
{
	return testInstances;
}

uint8_t Factory::getSDInstances()
{
  return testInstances;
}

uint8_t Factory::getIMUInstances()
{
  return imuInstances;
}
