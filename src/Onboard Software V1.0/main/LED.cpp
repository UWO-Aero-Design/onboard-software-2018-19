#include <stdint.h>

#include "Arduino.h"
#include "LED.h"
#include "Config.h"

LED::LED(uint8_t pin){
	this->pin = pin;
	pinMode(pin, OUTPUT);

}

LED::LED(LEDPIN pin){
	this->pin = (int) pin;
	pinMode(pin, OUTPUT);
}

// TODO: Use efficient digital write not the arduino version
void LED::turnOn(){
	digitalWrite(pin, HIGH);
}

// TODO: Use efficient digital write not the arduino version
void LED::turnOff(){
	digitalWrite(pin, LOW);
}