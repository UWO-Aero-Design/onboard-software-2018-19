#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>
#include <map>
#include <iterator>

#include "LED.h"
#include "Config.h"

class Event{
	private:
		map <uint8_t, LED *> boardLEDMap; 

		uint8_t errorPin;
		uint8_t powerPin;
		uint8_t statusPin;
		uint8_t commPin;

		struct LEDPWM{
			uint8_t _pin;
			int _period;
			int _duration;
			float _dutyCycle; 
		};

		void threadLEDBlink(struct LEDPWM ledpwm);

	protected:
	
	public:
		Event();
		Event(uint8_t errorLEDPin, uint8_t powerLEDPin, uint8_t statusLEDPin, uint8_t commLEDPin);
		~Event();

		void setLEDPins(uint8_t errorLEDPin, uint8_t powerLEDPin, uint8_t statusLEDPin, uint8_t commLEDPin);

		void turnOnErrorLED();
		void turnOffErrorLED();

		void turnOnPowerLED();
		void turnOffPowerLED();

		void turnOnCommLED();
		void turnOffCommLED();

		void turnOnStatusLED();
		void turnOffStatusLED();

		void flashErrorLed(int period, int duration);
		void flashPowerLed(int period, int duration);
		void flashCommLed(int period, int duration);
		void flashStatusLed(int period, int duration);

};

#endif // EVENT_H