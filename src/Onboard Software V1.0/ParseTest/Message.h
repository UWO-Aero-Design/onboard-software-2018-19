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

    char* buildMessageBuf(msg::aircraft_bits dataFields, void* data);
    uint16_t buildMessageType(uint8_t recipient);

    void parseMessage(msg::message_t msg);


};






#endif //PARSETEST_MESSAGE_H
