#ifndef FACTORY_H
#define FACTORY_H

#include <stdint.h>
#include "SDCardWriter.h"
#include "IMU.h"

// #include every object that needs to be created

class Factory{
	private:
		static uint8_t testInstances;
		static uint8_t radioInstances;
    static uint8_t sdInstances;
		static uint8_t imuInstances;
	protected:
	public:
		Factory();
		~Factory();

		uint8_t getTestInstances();
    uint8_t getSDInstances();
		uint8_t getIMUInstances();

		uint8_t selectTest(uint8_t model);

		// TODO: Add GPS* type
		void selectGPS(uint8_t gpsModel);

		// TODO: Add IMU* type
		IMU* selectIMU(uint8_t imuModel);

   // TODO: Add SD* type
   SDCardWriter* selectSD(uint8_t sdModel);

		// TODO: Add all other components
};

#endif
