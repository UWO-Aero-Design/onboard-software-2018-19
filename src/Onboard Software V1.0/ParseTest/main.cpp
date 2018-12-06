
#include <iostream>
#include <cstring>
#include "Message.h"


int main() {
    msg::aircraft_message_t* air = new msg::aircraft_message_t{0,13,0,0,0,0,0,0,0,0,0,0,0,0};

    msg::aircraft_bits dataFields = static_cast<msg::aircraft_bits>(0);
    dataFields = static_cast<msg::aircraft_bits>(bitOp::setBit(dataFields, msg::bLon));

    Message *msg = new Message();
    msg::message_t msgt = msg->buildMessage(dataFields, 8, 1, air);

    msg->parseMessage(msgt);

//    int len = sizeof(msgt);
//    char *raw = new char[len];
//    memcpy(raw, &msgt, len);

    //bitOp::printHex(raw, len);

    return 0;

}
