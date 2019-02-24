#ifndef ONBOARD_SYSTEM_H
#define ONBOARD_SYSTEM_H

/*
 * File Purpose
 *    A simple extension of System.h to test if the System object method is viable
 *    Should use the factory
 */

#include <stdint.h>

#include "SPI.h"
#include "RH_RF95.h"

// Includes factory that includes sensor classes
#include "System.h"

class OnboardSystem : public System{
private:
  // Sensors and sensor factory
  Factory* factory;
  IMU_MPU6050* imu;
  Barometer* baro;
  GPS* gps;

  // SDCardWriter* sd;

  // Radio object
  RH_RF95 *rf95;

  // Led objects
  LED* ledReceived;
  LED* ledSent;

  // Drop locations of gliders and payload
  float gliderDropLat;
  float gliderDropLon;
  float payloadDropLat;
  float payloadDropLon;

  // Target location received from ground station
  float targetLat;
  float targetLon;

  // Tracking rssi and errors
  uint16_t errors;
  int8_t rssi;

  // Private function to process incoming message.
  // Returns true if message was for this specific radio address
  // Returns false if message was not for this specific radio address
  bool processIncomingPacket(msg::ground_to_board_msg_t* packet);
	
protected:
public:
	OnboardSystem();
	~OnboardSystem();

	void initSystem();
	void updateSystem();
};


#endif // ONBOARD_SYSTEM_H
