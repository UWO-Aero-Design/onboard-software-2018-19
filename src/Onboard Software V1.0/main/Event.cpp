#include <stdint.h>
#include <map>
#include <iterator>

#include "Event.h"
#include "LED.h"

#include "TeensyThreads.h"



Event::Event(){}

Event::Event(uint8_t errorLEDPin, uint8_t powerLEDPin, uint8_t statusLEDPin, uint8_t commLEDPin)
{
	LED *errorLED, *powerLED, statusLED, *commLED;

	errorPin 	= errorLEDPin;
	powerPin 	= powerLEDPin;
	statusPin 	= statusLEDPin;
	commPin 	= commLEDPin;

	errorLED 	= new LED(errorPin);
	powerLED 	= new LED(powerPin);
	statusLED 	= new LED(statusPin);
	commLED 	= new LED(commPin);

	boardLEDMap.insert(pair <uint8_t, LED *> (errorPin, errorLED));
	boardLEDMap.insert(pair <uint8_t, LED *> (powerPin, powerLED));
	boardLEDMap.insert(pair <uint8_t, LED *> (statusPin, statusLED));
	boardLEDMap.insert(pair <uint8_t, LED *> (commPin, commLED));
}

Event::~Event()
{
	// Clear map
}

// TODO: This can be done better, idk really know how thought. Maybe use enum for COMM, POWER, .... and then use the enum for calling the functions?
		// Suggestions?

void Event::turnOnErrorLED(){ boardLEDMap.at(errorPin)->turnOn(); }
void Event::turnOffErrorLED(){ boardLEDMap.at(errorPin)->turnOff(); }

void Event::turnOnPowerLED(){ boardLEDMap.at(powerPin)->turnOn(); }
void Event::turnOffPowerLED(){ boardLEDMap.at(powerPin)->turnOff(); }

void Event::turnOnStatusLED(){ boardLEDMap.at(statusPin)->turnOn(); }
void Event::turnOffStatusLED(){ boardLEDMap.at(statusPin)->turnOff(); }

void Event::turnOnCommLED(){ boardLEDMap.at(commPin)->turnOn(); }
void Event::turnOffCommLED(){ boardLEDMap.at(commPin)->turnOff(); }

void Event::flashErrorLed(int period, int duration, float dutyCycle = 50){
	struct LEDPWM ledpwm = {errorPin, period, duration, dutyCycle};
	threads.addThread(threadLEDBlink, ledpwm);
}

void Event::flashPowerLed(int period, int duration, float dutyCycle = 50){
	struct LEDPWM ledpwm = {powerPin, period, duration, dutyCycle};
	threads.addThread(threadLEDBlink, ledpwm);
}

void Event::flashCommLed(int period, int duration, float dutyCycle = 50){
	struct LEDPWM ledpwm = {commPin, period, duration, dutyCycle};
	threads.addThread(threadLEDBlink, ledpwm);
}

void Event::flashStatusLed(int period, int duration, float dutyCycle = 50){
	struct LEDPWM ledpwm = {statusPin, period, duration, dutyCycle};
	threads.addThread(threadLEDBlink, ledpwm);
}

void Event::threadLEDBlink(struct LEDPWM ledpwm){
	int elapsedTime, period, dutyCycle = ledpwm._duration, ledpwm._period;
	float dutyCycle = ledpwm._dutyCycle;
	uint8_t pin 	= ledpwm._pin;

	do{
		boardLEDMap.at(pin)->turnOn();
		delay( (unsigned long) (period * (dutyCycle / 100)));
		boardLEDMap.at(pin)->turnOff();
		delay( (unsigned long) (period * (1 - (dutyCycle / 100))));

		elapsedTime -= period;
	}while(elapsedTime > 0);

}