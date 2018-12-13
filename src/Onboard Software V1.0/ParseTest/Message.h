//
// Created by cbaro on 2018-11-30.
//

#ifndef PARSETEST_MESSAGE_H
#define PARSETEST_MESSAGE_H

#include "BitHandler.h"
#include "Data.h"


class Message {
private:
protected:
public:
    Message();
    ~Message();

    msg::message_t buildMessage(msg::aircraft_bits dataFields, uint8_t dataFieldsSize, uint8_t recipient, void* data);

    char* buildGroundstationMessageBuffer(msg::gnd_station_bits dataFields, void* data);
    char* buildAircraftMessageBuffer(msg::aircraft_bits dataFields, void* data);
    uint8_t buildMessageType(uint8_t recipient);

    bool isMessageValid(msg::message_t msg);
    bool crcCheck(unsecuredData_t packet, uint8_t checksum);
    uint8_t generateCRC(unsecuredData_t packet);

    void  parseAircraftMessage(msg::message_t msg);
    void  parseGroundStationMessage(msg::message_t msg);


};






#endif //PARSETEST_MESSAGE_H
