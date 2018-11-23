#include <stdint.h>
#include "TestSystem.h"
#include "LEDThreadTestSystem.h"

#define TEST 1
#define LED_THREAD 2

System *g_system;

// Global system type
uint8_t g_systemType;  

void setup(){
	Serial.begin(9600);

	g_systemType = LED_THREAD;
  
 	systemSelect(g_systemType);
  
    g_system->initSystem();
}

void loop(){
	g_system->updateSystem();
}

void systemSelect(uint8_t systemType){
	switch(systemType){
		case TEST:
			g_system = new TestSystem();
			break;
		case LED_THREAD:
			g_system = new LEDThreadTestSystem();
		default:
			break;
	}
}
