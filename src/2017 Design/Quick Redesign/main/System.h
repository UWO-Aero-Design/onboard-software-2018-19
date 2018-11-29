#ifndef SYSTEM_H
#define SYSTEM_H

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
