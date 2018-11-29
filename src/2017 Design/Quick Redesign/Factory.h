#ifndef FACTORY_H
#define FACTORY_H

#include <stdint.h>

// #include every object that needs to be created

class Factory{
	private:
		static uint8_t testInstances;
		static uint8_t radioInstances;
	protected:
	public:
		Factory();
		~Factory();

		uint8_t getTestInstances();

		uint8_t selectTest(uint8_t model);

		// TODO: Add GPS* type
		void selectGPS(uint8_t gpsModel);
		
		// TODO: Add IMU* type
		void selectIMU(uint8_t imuModel);

		// TODO: Add all other components
}