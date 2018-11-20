#ifndef TEST_SYSTEM_H
#define TEST_SYSTEM_H

#include <stdint.h>

#include "System.h"

class TestSystem : public System{
	private:
		uint8_t testObject;
    SDCardWriter* sd;
		IMU* imu;
	protected:
	public:
		TestSystem();
		~TestSystem();

		void initSystem();
		void updateSystem();
};


#endif // TEST_SYSTEM_H
