#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include <stdint.h>

// Basic IMU data. Right now all variables are doubles, but look to reduce data type sizes as needed
typedef struct imu_t{
	uint8_t active;
	double xLinAccel;
	double yLinAccel;
	double zLinAccel;
	double xAngAccel;
	double yAngAccel;
	double zAngAccel;
	double Yaw;
	double Pitch;
	double Roll;
} __attribute__((__packed__)) IMUData;

// Basic GPS data. Right now all variables are doubles, but look to reduce data type sizes as needed
typedef struct gps_t{
	uint8_t active;
	double Latitude;
	double Longitude;
	double Speed;
	double X;
	double Y;
	double Z;
} __attribute__((__packed__)) GPSData;

// Basic barometer data. Right now all variables are doubles, but look to reduce data type sizes as needed
typedef struct barometer_t{
	uint8_t active;
	double Altitude;
	double Temperature;
	double Pressure;
} __attribute__((__packed__)) BarometerData;

// All sensor data. If a new sensor type is added, a new struct is needed
typedef struct sensorData_t{
	IMUData imu;
	GPSData gps;
	BarometerData barometer;
} __attribute__((__packed__))SensorData;

// Plane data structure, to be extended with fields seperate from sensor data
typedef struct planeData_t{
	SensorData sensorData;

} __attribute__((__packed__)) PlaneData;

// Glider data structure, to be extended with fields seperate from sensor data
typedef struct glider_t{
	SensorData sensorData;
	double yawControl;
	double pitchControl;

} __attribute__((__packed__)) #include "SystemControl.h"
#include "Config.h"
#include "Radio.h"
#include "Sensors.h"
#include "Motors.h"
#include "SystemAlgorithms.h";

#endif // SYSTEMDATA_H