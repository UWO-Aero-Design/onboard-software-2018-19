#include "Sensors.h"

Sensors::Sensors(){
	// Init structure
}

void Sensors::init(systemType sysTyp){
	switch(sysTyp){
		case SYS_PLANE:
			imu.init();
			sensorData.imu.active = 0x01;

			gps.init()
			sensorData.gps.active = 0x01;

			barometer.init();
			sensorData.barometer.active = 0x01;

			break;
		case SYS_GROUNDSTATION:
			break;

		case SYS_GLIDER:
			imu.init();
			sensorData.imu.active = 0x01;

			break;
			
		default:
			break;
	}
}

void Sensors::read(){
	if(sensorData.imu.active == 0x01){
		imu.update();
		sensorData.imu = imu.getData();
	}

	if(sensorData.gps.active == 0x01){
		gps.update();
		sensorData.gps = gps.getData();
	}

	if(sensorData.barometer.active == 0x01){
		barometer.update();
		sensorData.barometer = barometer.getData();
	}
}

SensorData Sensors::getPacket(){
	return sensorData;
}

int Sensors::getPacketSize(){
	return sizeof(sensorData);
}

