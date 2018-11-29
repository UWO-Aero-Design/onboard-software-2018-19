#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * File Purpose
 *    This is an abstract class that is reusable to allow for easy extension of the basic functionalities of a system
 *    With this class, different modes can be easily created
 *    We can extend this into a plane system, where the update and init focus on plane operation
 *    Or this can be booted into a LED test system, where we can test the LED class's independent of all other libraries
 */
 
#include "Factory.h"

class System{
	private:

	protected:
		Factory *factory;
		
	public:
		System(){}
		virtual ~System(){}

		virtual void initSystem() = 0;
		virtual void updateSystem() = 0;
};

#endif // SYSTEM_H
