#ifndef GPS_H
#define GPS_H

#include <stdint.h>

class GPS {
  public:

    float x, y, z;
    float baseLatitude, baseLongitude, baseAltitude;
    double lonToMetre, latToMetre; 
    
    void getZero(float latitude, float longitude, float MSLAlt); //returns starting reference, call once at the beginning
    void getXYZ(float latitude, float longitude, float MSLAlt, float baseLatitude, float baseLongitude); //returns the change in X and Y position, and the current alt in meters

    virtual void init();
    virtual void update();
    
    //float getZero(); //returns starting reference, call once at the beginning
    //float getXYZ(); //returns the change in X and Y position, and the current alt in meters

};

#endif
