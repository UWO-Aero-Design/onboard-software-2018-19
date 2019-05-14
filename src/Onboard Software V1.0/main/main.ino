#include <stdint.h>
#include "Config.h"

//#include "TestSystem.h"
//#include "LEDTestSystem.h"
//#include "GroundstationSystem.h"
#include "OnboardSystem.h"


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
  
  systemSelect(ONBOARD);
  
    g_system->initSystem();
}

void loop(){
  g_system->updateSystem();
}

void systemSelect(uint8_t systemType){
  switch(systemType)
  {
    case GROUNDSTATION:
    {
      Serial.println("Building groundstation object ... ");
      //g_system = new Groundstation();
    } break;
    case ONBOARD:
    {
      Serial.println("Building onboard object ... ");
      g_system = new OnboardSystem();
    } break;
    default:
    {
      Serial.println("Building nothing ... ");
      // default
    } break;
  }
}
