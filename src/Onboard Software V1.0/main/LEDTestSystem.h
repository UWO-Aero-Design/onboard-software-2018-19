#ifndef LED_TEST_SYSTEM_H
#define LED_TEST_SYSTEM_H

/*
 * File Purpose
 *    The purpose of this file is to extend System.h so we can easily check if the onboard LEDs 
 *    And the LED class is working as expected. Furthermore, this demonstrates how to use the 
 *    LED class.
 */
 
#include <stdint.h>
#include "System.h"

class LEDTestSystem : public System{
private:
	LED* testLED1;
  	LED* testLED2;
  	LED* testLED3;
  	LED* testLED4;
protected:
public:
	LEDTestSystem();
	~LEDTestSystem();

	void initSystem();
	void updateSystem();
};


#endif // LED_TEST_SYSTEM_H
