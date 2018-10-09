#ifndef GLIDER_H
#define GLIDER_H

#include "SystemControl.h"
#include "Config.h"
#include "Radio.h"
#include "Sensors.h"
#include "Motors.h"
#include "SystemAlgorithms.h"

class Glider : public SystemControl{
  private:
  	GliderData data;
  	uint8_t autoStatus;
  public:
  	Glider();
  	void init();
    void update();
    
};

#endif // GLIDER_H
