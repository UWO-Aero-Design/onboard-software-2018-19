#include "motorControl.h"

motorControl::motorControl(){

}

void motorControl::init(systemType sysTyp, uint8_t motorType){
	switch(sysTyp){
		case PLANE:

			if(motorType == _SERVO){
				servoBrd.init();
			}

			break;

		case GROUNDSTATION:
			break;

		case GLIDER:

			if(motorType == _OTHER){
				
			}

			break;
			
		default:
			break;
	}
}