//
// Created by cbaro on 2018-11-30.
//

#ifndef PARSETEST_MESSAGE_H
#define PARSETEST_MESSAGE_H

#include <stdint.h>
#include "BitHandler.h"

namespace msg{
    typedef enum{bLat, bLon, bYaw, bPitch, bRoll, bSpeed, bAltitude, bPIDYaw, bPIDPitch, bPIDRoll, bDropLat, bDropLon, bRSSI, bErrorCode} aircraft_bits;

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

    const uint8_t startByte     = 0x0A;
    const uint8_t endByte       = 0x0F;
}

class Message {
private:
    BitHandler *bitHandler;
protected:
public:
    Message();
    ~Message();
    msg::message_t buildMessage(msg::aircraft_bits dataFields, uint8_t dataFieldsSize, uint8_t recipient, void* data);

    char* buildMessageBuf(msg::aircraft_bits dataFields, char* buf, void* data);
    uint16_t buildMessageType(uint8_t recipient);

    void parseMessage(msg::message_t msg);


};






#endif //PARSETEST_MESSAGE_H
