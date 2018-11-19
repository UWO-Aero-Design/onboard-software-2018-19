#ifndef LED_H
#define LED_H

#include <stdint.h>

#include "Config.h"

class LED{
private:
	uint8_t pin;
public:
	LED(uint8_t pin);
	LED(LEDPIN pin);

	void turnOn();

	void turnOff();
	
};

#endif
