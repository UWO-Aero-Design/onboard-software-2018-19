/*
 * File Purpose
 *   Implementing TestSystem.h functions
 */

// For delay and serial
#include "Arduino.h"

#include "TestSystem.h"
#include "Factory.h"

TestSystem::TestSystem()
{
	factory = new Factory();
}

TestSystem::~TestSystem() {
	// Empty	
}

void TestSystem::initSystem()
{
  
}

void TestSystem::updateSystem()
{
	Serial.print("Instances: ");
	Serial.println(factory->getIMUInstances());
	
 
	delay(500);
}
