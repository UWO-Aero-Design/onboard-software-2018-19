#ifndef LED_H
#define LED_H

#include <stdint.h>

class LED{
private:
	uint8_t pin;

	// True means led is ON, false means led is OFF
	bool state;
	
public:
	LED(uint8_t pin);

	void turnOn() volatile;
	void turnOff() volatile;

	bool getState() const;
};

#endif
