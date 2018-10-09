#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H

#include "Config.h"
#include "Radio.h"
#include "Sensors.h"
#include "Motors.h"
#include "SystemAlgorithms.h"

class SystemControl{
  private:

  protected:
  	SystemType sysTyp;
    MotorControl motorCtrl;
  	Sensors sensors;
  	Radio radio;
    Bluetooth bluetooth;
    MessageParser msgParse;
    SystemAlgorithms sysAlgos;
  	
  	unsigned long sensorCurrMs;
  	unsigned long sensorPrevMs;
    unsigned long commCurrMs;
    unsigned long commPrevMs;

  public:
  	SystemControl();

    void _handleCmd(CommandType cmd);

    virtual void init();
    virtual void update();
    
};

#endif // SYSTEMCONTROL_H
