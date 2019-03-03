//#ifndef GROUNDSTATION_SYSTEM_H
//#define GROUNDSTATION_SYSTEM_H
//
//#include "SoftwareSerial.h"
//#include <stdint.h>
//#include "SPI.h"
//#include "RH_RF95.h"
//#include "System.h"
//
//#include "Config.h"
//
//const uint8_t buffersize = sizeof(msg::ground_to_board_msg_t);
//
//class Groundstation : public System{
//private:
//  // Radio object
//  RH_RF95 *rf95;
//  uint16_t RADIO_MSG_RATE_MS = 1000;
//  uint16_t RADIO_MSG_RATE_MS = 500;
//
//  // Led objects
//  LED* ledBluetooth;
//  LED* ledRadio;
//  LED* ledLoop;
//
//  // Bluetooth
//  char _buffer[buffersize];
//  bool bufferFilled;
//
//  uint8_t _start = msg::startByte;
//  uint8_t _end = msg::endByte;
//
//  uint8_t fails = 0;
//
//  bool started;
//  bool ended;
//  uint8_t index;
//
//  void printPlaneBuffer(char* buf);
//
//protected:
//public:
//  Groundstation();
//  ~Groundstation();
//
//  void initSystem();
//  void updateSystem();
//};
//
//#endif // GROUNDSTATION_SYSTEM_H
