#include <stdint.h>
#include "Config.h"

//#include "TestSystem.h"
//#include "LEDTestSystem.h"
#include "GroundstationSystem.h"
//#include "OnboardSystem.h"


#define TEST 1
#define LED_TEST 2
#define BLUETOOTH_TEST 3
#define GROUNDSTATION 4
#define ONBOARD 5

System *g_system;

// Global system type
uint8_t g_systemType;  

void setup(){
	Serial.begin(9600);
  
 	systemSelect(GROUNDSTATION);
  
    g_system->initSystem();
}

void loop(){
	g_system->updateSystem();
}

void systemSelect(uint8_t systemType){
	switch(systemType){
		// case TEST:
		// 	g_system = new TestSystem();
		// 	break;
		// case LED_TEST:
		// 	g_system = new LEDTestSystem();
		// 	break;
		// case BLUETOOTH_TEST:
		// 	g_system = new HC05TestSystem();
		// 	break;
		case GROUNDSTATION:
		{
			g_system = new Groundstation();
		} break;
    case ONBOARD:
    	{
      		//g_system = new OnboardSystem();
    	} break;
		default:
		{
			// default
		} break;
	}
}
