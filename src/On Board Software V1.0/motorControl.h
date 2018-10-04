#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "stdint.h"
#include "Config.h"


class motorControl{
  private:

  public:
  	motorControl();
  	
  	void init(systemType sysTyp, int motorType);

  	virtual void init() = 0;
  	virtual void drop() = 0;
};

#endif // MOTORCONTROL_H
