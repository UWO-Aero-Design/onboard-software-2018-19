#include <stdint.h>

#include "Arduino.h"
#include "LED.h"
#include "Config.h"

LED::LED(uint8_t pin){
	this->pin = pin;
	pinMode(pin, OUTPUT);

}

// TODO: Use efficient digital write not the arduino version
void LED::turnOn() volatile{
	digitalWrite(pin, HIGH);
}

// TODO: Use efficient digital write not the arduino version
void LED::turnOff() volatile{
	digitalWrite(pin, LOW);
}
