#include <stdint.h>

#include "Factory.h"
#include "SDCardWriter.h"
#include "SDCardWriter_Teensy.h"

// Initializing static class variables
uint8_t Factory::testInstances = 0;
uint8_t Factory::radioInstances = 0;
uint8_t Factory::sdInstances = 0;

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

uint8_t Factory::getTestInstances()
{
	return testInstances;
}

uint8_t Factory::getSDInstances()
{
  return testInstances;
}
