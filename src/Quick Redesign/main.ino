#include "Factory.h"

void setup(){
	Factory factory;
	uint8_t test = factory.selectTest(5);
}

void loop(){
	Serial.print("Instances: ");
	Serial.println(test.getRadioInstances());
	
	Serial.print("Radio Type: ");
	Serial.println(test);

	delay(500);
}