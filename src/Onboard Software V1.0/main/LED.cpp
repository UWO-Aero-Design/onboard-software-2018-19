#include <stdint.h>

#include "Arduino.h"
#include "LED.h"
#include "Config.h"

// Initial constructor. Sets the pin, pinmode, and sets initial state as false
LED::LED(uint8_t pin){
	this->pin = pin;
	state = false;
	pinMode(pin, OUTPUT);

}

// TODO: Use efficient digital write not the arduino version
// Turns on the LED and changes state to true
// Volatile for threading, no compiler optimzations
void LED::turnOn() volatile{
	digitalWrite(pin, HIGH);
	state = true;
}

// TODO: Use efficient digital write not the arduino version
// Turns off the LED and changes state to false
// Volatile for threading, no compiler optimzations
void LED::turnOff() volatile{
	digitalWrite(pin, LOW);
	state = false;
}

// Get state
bool getState const{
	return state;
}
