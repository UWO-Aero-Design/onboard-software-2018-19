#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include "SystemControl.h"
#include "Config.h"
#include "Radio.h"
#include "Sensors.h"
#include "Motors.h"
#include "SystemAlgorithms.h"

class Groundstation : public SystemControl{
  private:

  public:
  	Groundstation();
  	void init();
    void update();
    
};

#endif // GROUNDSTATION_H
