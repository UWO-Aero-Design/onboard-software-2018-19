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
  //Factory* factory;
  IMU_MPU6050* imu;
  Barometer* baro;
  GPS* gps;
  SDCardWriter* sd;
  ServoBoard* sb;

  // uint8_t  motor_pins[] = { servo1, servo2, servo3, servo4, motor1_on, motor1_dir, motor2_on, motor2_dir };
  // uint16_t motor_open[] = { servo1_open, servo1_open, servo1_open, servo1_open, motor1_open, motor2_open };
  // uint16_t motor_close[] = { servo1_close, servo1_close, servo1_close, servo1_close, motor1_close, motor2_close };

  // Radio object
  RH_RF95 *rf95;

  // Led objects
  LED* ledRadio;
  LED* ledLoop;
  LED* ledError;
  
  // Target location received from ground station
  float targetLat;
  float targetLon;

  // Packet to be sent back to tablet
  msg::board_to_ground_msg_t outgoing_packet;

  // Tracking rssi and errors
  uint16_t errors;
  int8_t rssi;

  // Private function to process incoming message.
  // Returns true if message was for this specific radio address
  // Returns false if message was not for this specific radio address
  uint8_t processIncomingPacket(msg::ground_to_board_msg_t* packet);

  // Generates test packet
  void generateTestPacket();
  void generateRealPacket();
  void printPacket();

  // flag for sending the lon/lat only once
  bool sendPDrop = false;
  bool sendGDrop = false;

  // motor/servo functions
  bool openDoors();
  bool closeDoors();
  bool dropPayload();
  bool dropGlider();

  // DC motor start
  unsigned long gliderDropTime = 0;
	
protected:
public:
	OnboardSystem();
	~OnboardSystem();

	void initSystem();
	void updateSystem();
};


#endif // ONBOARD_SYSTEM_H
