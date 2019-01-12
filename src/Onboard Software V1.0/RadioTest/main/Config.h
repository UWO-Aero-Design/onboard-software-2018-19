#ifndef CONFIG_H
#define CONFIG_H

/*
 * Author: Carl Baron - Nov 2018
 * File Purpose
 *    The purpose of this file is to store all system default structs
 *    As well as consts, defines, any magic numbers
 */

#include "Arduino.h"

// TODO(Carl Baron: Jan 10th, 2019): Global project namespaces, specific one for message
namespace msg{
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

    const uint8_t startByte     = 0x0A;
    const uint8_t endByte       = 0x0F;
};

namespace config{
    typedef enum {sysPlane, sysGndStation, sysGlider1, sysGlider2} systems_t;

    // TODO set this system type based on which system we are
    const systems_t thisSystem = sysPlane;
}

#endif // CONFIG_H