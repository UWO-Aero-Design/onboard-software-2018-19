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

  imu = factory->selectIMU(0);
	imu->initIMU(-3675, -1303, 611, 73, 50, 14);
}

void TestSystem::updateSystem()
{
	imu->updateSensor();
  
	Serial.print("Instances: ");
	Serial.println(factory->getSDInstances());

	Serial.print("Radio Type: ");
	Serial.println(testObject);

  Serial.print("Sd Success init (1 = true): ");
  Serial.println(!sd->isError());

	Serial.print("IMU instances: ");
  Serial.println(factory->getIMUInstances());
  //imu->printYPR();
	delay(500); // 500ms will produce a FIFO overflow on IMU
}
