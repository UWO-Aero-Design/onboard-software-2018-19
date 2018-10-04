#include "Sensors.h"

Sensors::Sensors(){

}

void Sensors::init(systemType sysTyp){
	switch(sysTyp){
		case PLANE:
			imu.init();
			gps.init()
			barometer.init();
			break;

		case GROUNDSTATION:
			break;

		case GLIDER:
			imu.init();
			break;
			
		default:
			break;
	}
}