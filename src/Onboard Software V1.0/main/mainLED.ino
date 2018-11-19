#include "Event.h"

Event *eventHandler;

#define TEST_MODE 1

int createdThread = 0;

unsigned long lastTime = 0;

void setup(){
	Serial.begin(9600);
	eventHandler = new Event(GREEN_LED, RED_LED, YELLOW_LED, BLUE_LED);
	lastTime = millis();
}

void loop(){

	// TEST on/off
	if(TEST_MODE){
		eventHandler.turnOnPowerLED();
		delay(1500);
		eventHandler.turnOffPowerLED();
		delay(1500);
	}

	// TEST blink thread. Thread should not interfere with timing of serial.print
	// TODO: How to know when I can recreate thread. Use ID which is return of addThread
	else{
	
		if(createdThread == 0){
			eventHandler.flashPowerLED(1000, 3000);
			createdThread = 1;
		}

		// Serial print timing should always be 20 even if thread interferes. 
		delay(20);
		Serial.println(millis() - lastTime);
		lastTime = millis();
		


		
	}
	

	
}