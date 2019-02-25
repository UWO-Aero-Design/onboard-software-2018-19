#ifndef GROUNDSTATION_SYSTEM_H
#define GROUNDSTATION_SYSTEM_H

#include <stdint.h>
#include "SPI.h"
#include "RH_RF95.h"
#include "HC05.h"
#include "System.h"

class Groundstation : public System{
private:
  SoftwareSerial *myPort;
  HC05 *bluetooth;
  RH_RF95 *rf95

  // Led objects
  LED* ledReceived;
  LED* ledSent;

  int RADIO_MSG_RATE_MS = 1000;

  char* bleBuffer;
  bool bufferFilled;

protected:
public:
  Groundstation();
  ~Groundstation();

  void initSystem();
  void updateSystem();
};

#endif // GROUNDSTATION_SYSTEM_H