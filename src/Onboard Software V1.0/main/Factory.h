#ifndef FACTORY_H
#define FACTORY_H

/*
 * File Purpose
 *    The purpose of this file is to be a factory, which is a OOP design pattern
 *    A factory seeks to encapsulate all object creation away from the main 
 *    This is useful because it stream lines the addition of a new project and the modification of its constructor
 *    https://sourcemaking.com/design_patterns/factory_method
 */

#include <stdint.h>
// #include every object that needs to be created
#include "LED.h"

class Factory{
private:
	static uint8_t testInstances;
protected:
public:
	Factory();
	~Factory();

 	// Return the number of test objects that have been created. 
	uint8_t getTestInstances();

	uint8_t   selectTest(uint8_t model);
  	LED*      selectLED(uint8_t ledPin);
};

#endif // FACTORY_H
