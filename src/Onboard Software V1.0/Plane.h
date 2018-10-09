#ifndef PLANE_H
#define PLANE_H

#include "SystemControl.h"
#include "Config.h"
#include "Radio.h"
#include "Sensors.h"
#include "Motors.h"
#include "SystemAlgorithms.h"

class Plane : public SystemControl{
  private:
  	PlaneData data;
  public:
  	Plane();
  	void init();
    void update();
    
};

#endif // PLANE_H
