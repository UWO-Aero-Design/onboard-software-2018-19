#include "systemControl.h"

// Constructor for system control. 
systemControl::systemControl(){
	currMs = 0;
	prevMs = 0;
}

void systemControl::init(){
	communications.init(sysTyp);
	sensors.init(sysTyp);
	motorCtrl.init(sysTyp, _SERVO);
}

void systemControl::zeroSystem(){
	sensors.zero(sysTyp);
	communications.zero(sysTyp);
	motorCtrl.zero(sysTyp);
}

