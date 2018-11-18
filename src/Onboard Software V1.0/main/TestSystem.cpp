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
  sd = factory->selectSD(0);
  sd->initSD();
}

void TestSystem::updateSystem()
{
	Serial.print("Instances: ");
	Serial.println(factory->getSDInstances());
	
	Serial.print("Radio Type: ");
	Serial.println(testObject);

  Serial.print("Sd Success init (1 = true): ");
  Serial.println(!sd->isError());
	delay(500);
}
