#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H

#include "Config.h"
#include "Communication.h"
#include "Sensors.h"
#include "motorControl.h"
#include "controlAlgorithms.h"

class systemControl{
  private:

  protected:
  	systemType sysTyp;
  	Sensors sensors;
  	Communications communications;
  	motorControl motorCtrl;
  	
  	unsigned long currMs;
  	unsigned long prevMs;
  public:
  	systemControl();
  	void init();
    virtual void update() =0;
    
};

#endif // SYSTEMCONTROL_H
