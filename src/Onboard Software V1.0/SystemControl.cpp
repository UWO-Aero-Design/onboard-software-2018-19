#include "systemControl.h"

// Constructor for system control. 
SystemControl::SystemControl(){
	sensorCurrMs = 0;
  	sensorPrevMs = 0;
    commCurrMs = 0;
    commPrevMs = 0;
}

 void SystemControl::_handleCmd(CommandType cmd){
 	switch(cmd){
 		case LOAD:
 			Serial.print("Load");
 			break;
 		case UNLOAD:
 			Serial.print("Unload");
 			break;
 		case ZERO:
 			Serial.print("Zero");
 			break;
 		case BAY_OPEN:
 			Serial.print("Bay Open");
 			break;
 		case BAY_CLOSE:
 			Serial.print("Bay Close");
 			break;
 		case DROP:
 			Serial.print("Drop");
 			//setDropHeight();
 			break;
 	}
 }