#include "GPS.h"
#include <Arduino.h>

void GPS::init() {
	Serial4.begin(38400);
}

void GPS::update() {
  if (Serial4.available() > 100) {
    pos = 0;
    _checksum = 0;
    Serial4.flush();
  }
  
	while(Serial4.available()) {
		char c = Serial4.read();

		if (c == '$') {
			if (pos > 5 && buf[pos-5] == '*') {
				if (!strncmp(buf, "$GPGGA", 6)) {
					readGPGGA(buf, _checksum);
				} else if (!strncmp(buf, "$GPRMC", 6)) {
          readGPRMC(buf, _checksum);
				}
			}

			pos = 0;
			_checksum = 0;
		}

		buf[pos++] = c;
		_checksum ^= c;
	}
}

void GPS::zero() {
	zero(lat, lon);
}

void GPS::zero(float latitude, float longitude) {
	baseLat = latitude;
	baseLon = longitude;

	float latRad = 0.0174533*latitude;
	float lonRad = 0.0174533*longitude;

	latToMetre = 111132.92 - 559.82*cos(2*latRad) + 1.175*cos(4*latRad) - 0.0023*cos(6*latRad);
	lonToMetre = 111412.84*cos(lonRad) - 93.5*cos(3*lonRad) + 0.118*cos(5*lonRad);
}

void GPS::readGPGGA(char *buf, uint8_t checksum) {
	uint8_t hour, min;
	float sec;
	uint16_t latDeg, lonDeg;
	float latMin, lonMin;
	char latHemi, lonHemi;
	float geoidHeight;

	int numParsed = sscanf(buf, "$GPGGA,%2d%2d%f,%2d%f,%c,%3d%f,%c,%d,%d,%*f,%f,M,%f,M,,*%*x", &hour, &min, &sec, &latDeg, &latMin, &latHemi, &lonDeg, &lonMin, &lonHemi, &fix, &satellites, &alt, &geoidHeight);

	if (numParsed != 13)
		return;

  degMinToVal(latDeg, latMin, latHemi == 'N', lat);
  degMinToVal(lonDeg, lonMin, lonHemi == 'E', lon);

  latLonAltToXYZ(lat, lon, alt, x, y, z);

/*
  long curVTime = millis();
  if (curVTime - lastVTime > 3000) {
    float diffX = lastVX - x;
    float diffY = lastVY - y;
  
    speed = 1000 * sqrt(diffX * diffX + diffY * diffY) / (curVTime - lastVTime);

    if (speed > 3)
      course = 57.2957795 * atan2(diffX, diffY);

    lastVX = x;
    lastVY = y;
    lastVTime = curVTime;
  }
  */
}

void GPS::readGPRMC(char *buf, uint8_t checksum) {
	uint8_t hour, min;
  float sec;
  uint16_t latDeg, lonDeg;
  float latMin, lonMin;
  char latHemi, lonHemi;

	int numParsed = sscanf(buf, "$GPRMC,%2d%2d%f,%*c,%2d%f,%c,%3d%f,%c,%f,%f,%*d,%*f,%*d,,,A*%*x", &hour, &min, &sec, &latDeg, &latMin, &latHemi, &lonDeg, &lonMin, &lonHemi, &speed, &course);
  
  if (numParsed != 11)
    return;

  degMinToVal(latDeg, latMin, latHemi == 'N', lat);
  degMinToVal(lonDeg, lonMin, lonHemi == 'E', lon);

  x = lonToMetre*(lon - baseLon);
  y = latToMetre*(lat - baseLat);
  z = alt;
}

void GPS::readGPGSA(char *buf, uint8_t checksum) {

}

inline void GPS::degMinToVal(uint16_t deg, float min, bool pos, float &val) {
  val = deg + min/60;
  if (!pos) val = -val;
}

inline void GPS::latLonAltToXYZ(float lat, float lon, float alt, float &x, float &y, float &z) {
  x = lonToMetre*(lon - baseLon);
  y = latToMetre*(lat - baseLat);
  z = alt;
}

