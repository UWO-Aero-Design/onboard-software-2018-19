#ifndef GPS_H
#define GPS_H

#include <stdint.h>

class GPS{
  protected:
    double deltaX, deltaY, Z; //change in position for each axis
    double refLat, refLon, refAlt; //references

    double lat, lon, alt;//values common to most GPS units
    
  public:
    GPS();
    ~GPS();
    void getXYZ(float latitude, float longitude, float alt, float baseLatitude, float baseLongitude); //returns the change in X and Y position, and the current alt in meters
    void getZero(float latitude, float longitude, float alt); //returns starting reference

    virtual void init() = 0;
    virtual void update() = 0;
    virtual double getLat() = 0;
    virtual double getLon() = 0;
    virtual double getAlt() = 0;
    virtual uint32_t getSatellites() = 0;
};

#endif
