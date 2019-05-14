#include <stdint.h>
#include <Arduino.h>
#include "GPS.h"
#include "GPS_ETV4.h"

//getZero and getXYZ can be used with any GPS unit (not specific to ETV4)

void GPS::getZero(float lat, float lon, float alt){
  baseLatitude = lat;
  baseLongitude = lon;
  baseAltitude = alt;
}

void GPS::getXYZ(float latitude, float longitude, float MSLAlt, float baseLatitude, float baseLongitude){
  //finds the diference in position from the reference (zero) in meters
  double latRad = 0.0174533*latitude;
  double lonRad = 0.0174533*longitude;  
  latToMetre = 111132.92 - 559.82*cos(2*latRad) + 1.175*cos(4*latRad) - 0.0023*cos(6*latRad);
  lonToMetre = 111412.84*cos(lonRad) - 93.5*cos(3*lonRad) + 0.118*cos(5*lonRad);
  
  x = lonToMetre*(longitude - baseLongitude);
  y = latToMetre*(latitude - baseLatitude);
  z = (baseAltitude-MSLAlt); 
}

/*GPS_ETV4 gps;

gps.update();
gps.getZero(gps.latitude, gps.longitude, gps.MSLAlt);
gps.getXYZ(gps.latitude, gps.longitude, gps.MSLAlt, gps.baseLatitude, gps.bangitude);
*/
