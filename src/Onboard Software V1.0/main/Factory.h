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
#include "config.h"
#include "LED.h"
#include "IMU_MPU6050.h"
#include "Barometer.h"
#include "GPS_NEO6.h"
#include "SDCardWriter_Teensy.h"

class Factory{
  private:
  	static uint8_t IMUInstances;
    static uint8_t baroInstances;
    static uint8_t GPSInstances;
    static uint8_t SDInstances;
  protected:
  public:
  	Factory();
  	~Factory();
    IMU_MPU6050* selectIMU(uint8_t imu);
    Barometer* selectBaro(uint8_t imu);
    GPS* selectGPS(uint8_t gps);
    SDCardWriter* selectSD(uint8_t sd);
    LED* selectLED(uint8_t ledPin);
  
   	// Return the number of test objects that have been created. 
  	uint8_t getIMUInstances();
    uint8_t getBaroInstances();
    uint8_t getGPSInstances();
    uint8_t getSDInstances();
  	uint8_t   selectTest(uint8_t model);
};

#endif // FACTORY_H
