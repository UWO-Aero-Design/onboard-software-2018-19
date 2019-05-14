/*
 * File Purpose
 *    Implementing LEDSystemTest.h functions
 */

// For delay and serial
#include "Arduino.h"

#include "Factory.h"
#include "Config.h"
#include "LEDTestSystem.h"


LEDTestSystem::LEDTestSystem()
{
	factory = new Factory();
}

LEDTestSystem::~LEDTestSystem(){
	// Empty	
}

// Create each LED using Config enum
// Start threads for 3 LEDs
void LEDTestSystem::initSystem()
{
	testLED1 = factory->selectLED(BLUE_LED);
  testLED2 = factory->selectLED(RED_LED);
  testLED3 = factory->selectLED(GREEN_LED);
  testLED4 = factory->selectLED(YELLOW_LED);
  
	testLED1->startBlinking(100000,1000,75);
  testLED2->startBlinking(100000,1000,25);
  testLED3->startBlinking(100000,1000,50);
}

// Update loop
void LEDTestSystem::updateSystem()
{
  testLED4->turnOn();
}
