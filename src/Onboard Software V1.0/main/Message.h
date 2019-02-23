//
// Created by cbaro on 2018-11-30.
//

#ifndef PARSETEST_MESSAGE_H
#define PARSETEST_MESSAGE_H


#include "Config.h"

class Message {
private:
protected:
public:
    Message();
    ~Message();

    msg::message_t buildMessage(uint8_t recipient, msg::aircraft_message_t data);
    uint16_t buildMessageType(uint8_t recipient);

    char* buildGroundstationMessageBuffer(void* data);
    char* buildAircraftMessageBuffer(void* data);
    
    bool isMessageValid(msg::message_t msg);
    bool crcCheck(msg::unsecuredData_t packet, uint8_t checksum);
    uint8_t generateCRC(msg::unsecuredData_t packet);

    void  parseAircraftMessage(msg::message_t msg);
    void  parseGroundStationMessage(msg::message_t msg);


};






#endif //PARSETEST_MESSAGE_H
