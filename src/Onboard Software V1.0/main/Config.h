#ifndef CONFIG_H
#define CONFIG_H

/*
 * File Purpose
 *    The purpose of this file is to accumulate all configuration variables
 *    Having magic numbers is not good programming practice so use this to typedef and replace system magic numbers
 */
#include "Arduino.h"
#include "Macros.h"

enum LEDPIN{BLUE_LED = 27, GREEN_LED, YELLOW_LED, RED_LED};

namespace radio
{
    const uint8_t RFM95_CS  	  = 10;
    const uint8_t RFM95_RST 	  = 6;
    const uint8_t RFM95_INT 	  = 5;
    
    const float   RFM95_FREQUENCY = 915.0;
    const uint8_t RFM95_TX_POWER  = 23;
}

// TODO(Carl Baron: Jan 10th, 2019): Global project namespaces, specific one for message
namespace msg{

  const uint8_t GLIDER_DROP = 1;
  const uint8_t PAYLOAD_DROP = 2;

  const uint8_t CAL_IMU  = 1;
  const uint8_t CAL_GPS  = 2;
  const uint8_t CAL_BARO = 3;

  // Data flags for a message being sent from an aircraft to the groundstation
  typedef enum{airLat, airLon, airYaw, airPitch, airRoll, airSpeed, airAltitude, airPIDYaw,
      airPIDPitch, airPIDRoll, airDropLat, airDropLon, airRSSI, airErrorCode} AirToGndFlags;

  // Data flags for a message being sent from the groundstation to an aircraft
  typedef enum{gndTargetLat, gndTargetLon, gndCalibrate, gndRSSI, gndDropRequest, gndGliders,
      gndMotor1, gndMotor2, gndMotor3, gndMotor4, gndMotor5, gndMotor6, gndMotor7, gndMotor8,
      gndMotor9, gndMotor10, gndMotor11, gndMotor12, gndMotor13, gndMotor14, gndMotor15, gndMotor16, gndErrorCode} GndToAirFlags;

    typedef struct {
        uint8_t msgStart;
        uint16_t msgType;
        uint16_t dataID;
        char* buf;
        uint8_t msgEnd;
    } __attribute__((__packed__)) unsecuredData_t;

    typedef struct {
        unsecuredData_t packet;
        uint8_t checksum;
    } __attribute__((__packed__)) message_t;

    typedef struct {
        int32_t lat;
        int32_t lon;
        int16_t yaw;
        int16_t pitch;
        int16_t roll;
        uint16_t speed;
        uint16_t alt;
        int16_t pidYaw;
        int16_t pidPitch;
        int16_t pidRoll;
        int32_t dropLat;
        int32_t dropLon;
        uint8_t rssi;
        uint16_t error;
    } __attribute__((__packed__)) aircraft_message_t;

    typedef struct {
        int32_t targetLat;
        int32_t targetLon;
        uint8_t calibrate;
        uint8_t rssi;
        uint8_t dropRequest;
        uint8_t gliders;
        uint16_t motor1;
        uint16_t motor2;
        uint16_t motor3;
        uint16_t motor4;
        uint16_t motor5;
        uint16_t motor6;
        uint16_t motor7;
        uint16_t motor8;
        uint16_t motor9;
        uint16_t motor10;
        uint16_t motor11;
        uint16_t motor12;
        uint16_t motor13;
        uint16_t motor14;
        uint16_t motor15;
        uint16_t motor16;
        uint16_t error;
    } __attribute__((__packed__)) gnd_station_message_t;


    typedef struct 
    {
		uint8_t msgStart;
		uint16_t msgType;
		int32_t targetLat;
        int32_t targetLon;
        uint8_t calibrate;
        uint8_t rssi;
        uint8_t dropRequest;
        uint8_t gliders;
        uint16_t motor1;
        uint16_t motor2;
        uint16_t motor3;
        uint16_t motor4;
        uint16_t motor5;
        uint16_t motor6;
        uint16_t motor7;
        uint16_t motor8;
        uint16_t motor9;
        uint16_t motor10;
        uint16_t motor11;
        uint16_t motor12;
        uint16_t motor13;
        uint16_t motor14;
        uint16_t motor15;
        uint16_t motor16;
        uint16_t error;
		uint8_t msgEnd;
	} __attribute__((__packed__)) ground_to_board_msg_t;



	typedef struct {
		uint8_t msgStart;
		uint16_t msgType;
        int32_t lat;
        int32_t lon;
        int16_t yaw;
        int16_t pitch;
        int16_t roll;
        uint16_t speed;
        uint16_t alt;
        int16_t pidYaw;
        int16_t pidPitch;
        int16_t pidRoll;
        int32_t gDropLat;
        int32_t gDropLon;
        int32_t pDropLat;
        int32_t pDropLon;
        int8_t rssi;
        uint16_t error;
        uint8_t msgEnd;
    } __attribute__((__packed__)) board_to_ground_msg_t;



    const uint8_t startByte     = 0x0A;
    const uint8_t endByte       = 0xFF;
}

namespace config{
    typedef enum {sysPlane, sysGndStation, sysGlider1, sysGlider2} systems_t;

    // TODO set this system type based on which system we are
    const systems_t thisSystem = sysPlane;
}

// As of Onboard PCB V1.0, these are the pin mappings for the LEDs
// Blue = 27, Green = 28, Yellow = 29, Red = 30


#endif // CONFIG_H
