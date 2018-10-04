#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include "systemControl.h"
#include "Config.h"
#include "Communication.h"
#include "Sensors.h"
#include "motorControl.h"
#include "controlAlgorithms.h"

class Groundstation : public systemControl{
  private:

  public:
  	Groundstation();
    void update();
    
};

#endif // GROUNDSTATION_H
