#include <stdint.h>
#include "TestSystem.h"

#define TEST 1

System *g_system;

// Global system type
uint8_t g_systemType;  

void setup(){
	Serial.begin(9600);

	g_systemType = TEST;
  
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
		default:
			break;
	}
}
