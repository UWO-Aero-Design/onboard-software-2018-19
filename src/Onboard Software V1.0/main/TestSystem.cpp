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

TestSystem::~TestSystem(){
	// Empty	
}

void TestSystem::initSystem()
{
	testObject = factory->selectTest(0);
}

void TestSystem::updateSystem()
{
	Serial.print("Instances: ");
	Serial.println(factory->getTestInstances());
	
	Serial.print("Test Type: ");
	Serial.println(testObject);
 
	delay(500);
}
