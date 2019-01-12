//
// Created by cbaro on 2018-11-30.
//

#ifndef PARSETEST_MESSAGE_H
#define PARSETEST_MESSAGE_H

#include "BitManipulation.h"
#include "Config.h"


class Message {
private:
protected:
public:
    Message();
    ~Message();

    msg::message_t buildMessage(msg::AirToGndFlags dataFields, uint8_t recipient, void* data);

    char* buildGroundstationMessageBuffer(msg::GndToAirFlags dataFields, void* data);
    char* buildAircraftMessageBuffer(msg::AirToGndFlags dataFields, void* data);
    uint16_t buildMessageType(uint8_t recipient);

    bool isMessageValid(msg::message_t msg);
    bool crcCheck(msg::unsecuredData_t packet, uint8_t checksum);
    uint8_t generateCRC(msg::unsecuredData_t packet);

    void  parseAircraftMessage(msg::message_t msg);
    void  parseGroundStationMessage(msg::message_t msg);


};






#endif //PARSETEST_MESSAGE_H
