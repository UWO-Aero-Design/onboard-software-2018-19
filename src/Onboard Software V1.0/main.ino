#include "Config.h"
#include "SystemControl.h"

// System control object
SystemControl systemCtl;

void setup(){
	modeSelect();
	systemCtl.init();
	delay(500);
}

void loop(){
	systemCtl.update();
}

void modeSelect(){
	switch(bootType){
		case PLANE:
			Serial.println("Boot in PLANE mode");
			systemCtl = Plane();
			break;

		case GROUNDSTATION:
			Serial.println("Boot in GROUNDSTATION mode");
			systemCtl = Groundstation();
			break;

		case GLIDER:
			Serial.println("Boot in GLIDER mode");
			systemCtl = Glider();
			break;
			
		default:
			Serial.println("Boot in DEFAULT mode");
			systemCtl = systemControl();
			break;
	}
}