#ifndef LED_THREADING_TEST_H
#define LED_THREADING_TEST_H

#include <TeensyThreads.h>
#include "LED.h"
#include "Runnable.h"
#include "System.h"

class LEDThreadTestSystem : public Runnable, public System{
private:

  volatile LED* led1;
  volatile LED* led2;
  volatile LED* led3;
  volatile LED* led4;

  std::thread *th1;

protected:
	void runTarget(void *arg);

public:
  LEDThreadTestSystem();
	void startThread();

  void initSystem();
  void updateSystem();

};

#endif // THREAD_TEST_H
