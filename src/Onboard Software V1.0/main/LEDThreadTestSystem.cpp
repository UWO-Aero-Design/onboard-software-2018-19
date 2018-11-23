#include "LEDThreadTestSystem.h"


LEDThreadTestSystem::LEDThreadTestSystem(){
	led1   = new LED(27);
    led2   = new LED(28);
    led3   = new LED(30);
    led4   = new LED(29);
}

void LEDThreadTestSystem::initSystem(){
	th1 = new std::thread(&Runnable::runThread, this);
    th1->detach();
}

void LEDThreadTestSystem::updateSystem(){
  	// empty
}


void LEDThreadTestSystem::runTarget(void *arg){
	LEDThreadTestSystem* test = static_cast<LEDThreadTestSystem*>(arg);

  while(1){
    test->led1->turnOn();
    threads.delay(1000);
    test->led1->turnOff();
    threads.delay(1000);
  }
    
}
