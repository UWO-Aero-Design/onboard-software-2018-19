#include<Arduino.h>
#include <stdint.h>
#include <TinyGPS++.h>

#include "GPS_NEO6.h"
#include "GPS.h"

GPS_NEO6::GPS_NEO6() {}
GPS_NEO6::~GPS_NEO6() {}

// To use TinyGPS++ library
TinyGPSPlus tgps2;

void GPS_NEO6::init(){
  Serial4.begin(9600);
}

void GPS_NEO6::update(){

  //insure data is current
  if (Serial4.available() > 100){
    Serial4.flush();
  }

  while(Serial4.available()>0){
    tgps2.encode(Serial4.read());
    if (tgps2.location.isUpdated()){
      lat = (tgps2.location.lat());
      lon = (tgps2.location.lng());
    }
    
    if (tgps2.altitude.isUpdated()){
      alt = tgps2.altitude.meters();
    }
    
    if (tgps2.date.isUpdated()){
      day = tgps2.date.day();
      month = tgps2.date.month();
      year = tgps2.date.year();
    }
    if (tgps2.time.isUpdated()){
      hour = tgps2.time.hour();
      min = tgps2.time.minute();
      sec = tgps2.time.second();
    }
    
    if (tgps2.speed.isUpdated()){
      speed = tgps2.speed.mps(); //do we want metres per sec, or different units?
    }
    if (tgps2.course.isUpdated()){
      course = tgps2.course.deg();
    }
    if (tgps2.satellites.isUpdated()){
      satellites = tgps2.satellites.value();
    }
    
   if (tgps2.hdop.isUpdated()){
      hdop = tgps2.hdop.value();
    }
  }
}
double GPS_NEO6::getLat(){
  return lat;
}

double GPS_NEO6::getLon(){
  return lon;
}

double GPS_NEO6::getAlt(){
  return alt;
}

uint8_t GPS_NEO6::getDay(){
  return day;
}

uint8_t GPS_NEO6::getMonth(){
  return month;
}

uint16_t GPS_NEO6::getYear(){
  return year; 
}

uint8_t GPS_NEO6::getHour(){
  return hour;
}

uint8_t GPS_NEO6::getMin(){
  return min;
}

uint8_t GPS_NEO6::getSec(){
  return sec;
}

double GPS_NEO6::getSpeed(){
  return speed;
}

double GPS_NEO6::getCourse(){
  return course;
}

float GPS_NEO6::getHdop(){
  return hdop;
}

uint32_t GPS_NEO6::getSatellites(){
  return satellites;
}
