/*
 * File Purpose
 *    Implementing Factory.h functions
 */

#include "Factory.h"

// Initializing static class variables
uint8_t Factory::testInstances = 0;

// Default constructor
Factory::Factory(){}

Factory::~Factory(){}

// Return the number of test objects that have been created. 
uint8_t Factory::getTestInstances()
{
	return testInstances;
}

// Test method for checking if the factory works and compiles
uint8_t Factory::selectTest(uint8_t testModel)
{
	// Returned object
	uint8_t object = 0;

	// Checking what model to create
	switch(testModel)
	{
		default:
		{
			object = 1;
      		++testInstances;
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
