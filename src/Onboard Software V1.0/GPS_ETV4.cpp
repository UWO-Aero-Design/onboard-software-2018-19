#include<Arduino.h>
#include <stdint.h>
#include "GPS_ETV4.h"
#include "GPS.h"

void GPS_ETV4::init(){
  Serial.begin(38400);
}

void GPS_ETV4::update(){

  //insure data is current
  if (Serial.available() > 100){
    pos = 0;
    Serial.flush();
  }

  while(Serial.available()){
    char inByte = Serial.read();
    
    //check if a complete output sentence has been formed
    if (String(inByte) = "$"){
      if (pos > 5 && String(data[pos - 5]) == "*"){
        
        //determine which type of output sentence to read
        if (strncmp(data, "$GPGGA", 6)){
          readGPGGA(data);
        }
        else if (strncmp(data, "$GPRMC",6)){
          readGPRMC(data);
        }
        else if (strncmp(data, "$GPGSA", 6)){
          readGPGSA(data);
        }
      }
      pos = 0;
    }
    data[pos++] = inByte;
    }
  }

void GPS_ETV4::readGPGGA(char data[256]){
  int numParsed = sscanf(data, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%*f,%f,M,%f,M,,%*x", &Time, &latitude, &NSInd, &longitude, &EWInd, &fix, &satellites, &MSLAlt, &geoSep);
  if (numParsed != 9){
    return;
  }
}

void GPS_ETV4::readGPRMC(char data[256]){
  int numParsed = sscanf(data, "$GPRMC,%f,%*c,%f,%c,%f,%c,%f,%f,%*d,,A*%*x",&Time, &latitude, &NSInd, &longitude, &EWInd, &Speed, &course);
  if (numParsed != 7){
    return;
  }
}

void GPS_ETV4::readGPGSA(char data[256]){
  int numParsed = sscanf(data, "$GPGSA,%c,%c,,,,,,,,,,,,,,%f,%f,%f,%*x", &mode1, &mode2, &PDOP, &HDOP, &VDOP);
  if (numParsed !=5){
    return;
  }
}
