#include "Plane.h"

// Constructor for the plane 
Plane::Plane(){
	this.sysTyp = PLANE;
}

// Function that is called on every system loop. Main control of the system type
void Plane::update(){
	currMs = millis();

	if(currMs - prevMs >= SENSOR_POLL_RATE_MS){
		prevMs = currMs;
		sensors.read();
	}

	// Struct where bytes line up
	sensorData = (sensorData_t)sensors.toByteString();

	if(interval){
		communications.send(sensorData);
	}

	int command = communications.recv();
	_processCmd(command);

	delay(SYSTEM_DELAY_MS);

}

void Plane::_processCmd(int cmd){
		
}