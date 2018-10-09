#include "Glider.h"

// Constructor for the glider
Glider::Glider(){
	this.sysTyp = SYS_GLIDER;
}

void Glider::init(){
	radio.init(sysTyp, RADIO_SLAVE);
	motorCtrl.init(sysTyp, _SERVO);
	sensors.init(sysTyp);
}

// Function that is called on every system loop. Main control of the system type
void Glider::update(){
	sensorCurrMs = millis();
	if(sensorCurrMs - sensorPrevMs >= GLIDER_SENSOR_POLL_RATE_MS){
		sensorPrevMs = sensorCurrMs;
		sensors.read();
	}
	
	int command = msgParse.verifyMsg(radio.recv());
	_handleCmd(command);

	if(autoStatus){
		// Autonomous gliding algorithm
	}
	
	delay(SYSTEM_DELAY_MS);
}

void Glider::setAutonomousFlight(uint8_t autoStatus){
	this.autoStatus = autoStatus;
}