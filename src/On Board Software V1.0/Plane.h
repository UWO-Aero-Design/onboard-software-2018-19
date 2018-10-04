#ifndef PLANE_H
#define PLANE_H

#include "systemControl.h"
#include "Config.h"
#include "Communication.h"
#include "Sensors.h"
#include "motorControl.h"
#include "controlAlgorithms.h"

class Plane : public systemControl{
  private:

  public:
  	Plane();
    void update();
    
};

#endif // PLANE_H
