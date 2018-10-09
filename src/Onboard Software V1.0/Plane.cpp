#include "Plane.h"

// Constructor for the plane 
Plane::Plane(){
	this.sysTyp = SYS_PLANE;
}

void Plane::init(){
	radio.init(sysTyp, RADIO_SLAVE);
	motorCtrl.init(sysTyp, _SERVO);
	sensors.init(sysTyp);
}

// Function that is called on every system loop. Main control of the system type
void Plane::update(){

	sensorCurrMs = millis();
	if(sensorCurrMs - sensorPrevMs >= SENSOR_POLL_RATE_MS){
		sensorPrevMs = sensorCurrMs;
		sensors.read();
	}

	commCurrMs = millis();
	if(commCurrMs - commPrevMs >= COMM_REFRESH_RATE_MS){
		commPrevMs = commCurrMs;
		radio.send(sensors.getPacket(), sensors.getPacketSize());
	}

	int command = msgParse.verifyMsg(radio.recv());
	_handleCmd(command);

	delay(SYSTEM_DELAY_MS);

}
