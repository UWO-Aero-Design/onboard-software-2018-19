//
// Created by cbaro on 2018-12-05.
//

#ifndef PARSETEST_DATA_H
#define PARSETEST_DATA_H

#include <cstdint>

namespace msg{
    typedef enum{bLat, bLon, bYaw, bPitch, bRoll, bSpeed, bAltitude, bPIDYaw, bPIDPitch, bPIDRoll, bDropLat, bDropLon, bRSSI, bErrorCode} aircraft_bits;
    typedef enum{} gnd_station_bits;

    typedef struct {
        uint8_t msgStart;
        uint8_t msgType;
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

    } __attribute__((__packed__)) gnd_station_message_t;

    const uint8_t startByte     = 0x0A;
    const uint8_t endByte       = 0x0F;
}

#endif //PARSETEST_DATA_H
