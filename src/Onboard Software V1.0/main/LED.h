#ifndef LED_H
#define LED_H

#include <stdint.h>

class LED{
private:
	uint8_t pin;
public:
	LED(uint8_t pin);

	void turnOn() volatile;

	void turnOff() volatile;
};

#endif
