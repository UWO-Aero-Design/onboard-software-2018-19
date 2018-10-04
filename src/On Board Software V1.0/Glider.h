#ifndef GLIDER_H
#define GLIDER_H

#include "systemControl.h"
#include "Config.h"
#include "Communication.h"
#include "Sensors.h"
#include "motorControl.h"
#include "controlAlgorithms.h"

class Glider : public systemControl{
  private:

  public:
  	Glider();
    void update();
    
};

#endif // GLIDER_H
