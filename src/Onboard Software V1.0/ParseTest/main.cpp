#include <iostream>
#include <cstring>
#include "Message.h"

int main() {
    msg::aircraft_message_t* air = new msg::aircraft_message_t{0,16,0,0,0,0,0,0,0,0,0,0,0,0};

    msg::aircraft_bits dataFields = static_cast<msg::aircraft_bits>(0);
    dataFields = static_cast<msg::aircraft_bits>(bitOp::setBit(dataFields, msg::airLon));

    Message *msg = new Message();
    msg::message_t msgt = msg->buildMessage(dataFields, 8, 1, air);

    msg->parseMessage(msgt);
    std::cout << std::endl;

//    uint8_t byte = 0;
//    uint8_t nibble1 = 10;
//    uint8_t nibble2 = 12;
//
//    printf("%02x ", byte & 0xFF);
//    std::cout << std::endl;
//
//    printf("%02x ", bitOp::setLowerByteNibble(byte, nibble1) & 0xFF);
//    std::cout << std::endl;
//
//    printf("%02x ", bitOp::setUpperByteNibble(byte, nibble2) & 0xFF);
//    std::cout << std::endl;
//
//    int len = sizeof(msgt);
//    char *raw = new char[len];
//    memcpy(raw, &msgt, len);
//
//    bitOp::printHex(raw, len);

    return 0;
}

