#ifndef GPS_H
#define GPS_H

#include <stdint.h>
#include <Wire.h>

#define GPS_ADDR              0x20
#define I2C_GPS_COMMAND       01
#define I2C_GPS_STATUS        0
#define I2C_GPS_LOCATION      07
#define I2C_GPS_GROUND_SPEED  31   // GPS ground speed in m/s*100 (uint16_t)      (Read Only)
#define I2C_GPS_ALTITUDE      33   // GPS altitude in meters (uint16_t)           (Read Only)
#define I2C_GPS_GROUND_COURSE 35   // GPS ground course (uint16_t)

#define MASK_2D      0x40
#define MASK_3D      0x20
#define MASK_NUM_SAT 0x0F

#define FIX_NONE     0
#define FIX_2D       1
#define FIX_3D       2

class GPS {
public:
	void init();
	void update();
	void zero();
	void zero(float latitude, float longitude);

	float lat, lon, alt;
	float x, y, z;
	float speed, course;
	uint8_t fix;
	uint8_t satellites;

private:
	void readGPGGA(char *buf, uint8_t checksum);
	void readGPRMC(char *buf, uint8_t checksum);
	void readGPGSA(char *buf, uint8_t checksum);

  inline void degMinToVal(uint16_t deg, float min, bool pos, float &val);
  inline void latLonAltToXYZ(float lat, float lon, float alt, float &x, float &y, float &z);

	char buf[256];
	uint8_t pos = 0;
	uint16_t _checksum = 0;
	float baseLat, baseLon;
	float latToMetre, lonToMetre;

  float lastVX, lastVY;
  long lastVTime;
};



#endif // GPS_H
