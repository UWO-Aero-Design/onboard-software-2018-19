#include <iostream>
#include <cstring>
#include "Message.h"

// NOTE: enum --> int is a safe cast but int --> enum an unsafe cast meaning we can pass an enum into an int param but we cannot pass an int into an enum param without casting

int main() {
    // Initialize aircraft message buffer for testing
    // Send to move this into the message but for now because we dont have a fully integrated system, skip this step
    msg::aircraft_message_t* air = new msg::aircraft_message_t{0,16,0,0,0,0,0,0,0,0,0,0,0,0};

    // Create data fields bit for determinining which data to send
    msg::aircraft_bits dataFields = static_cast<msg::aircraft_bits>(0);
    dataFields = static_cast<msg::aircraft_bits>(bitOp::setBit(dataFields, msg::airLon));

    // Build message handling object and use it to build a message_t for sending
    Message *msg = new Message();
    msg::message_t msgt = msg->buildMessage(dataFields, config::thisSystem, air);

    // Check if the message we sent is valid
    bool msgValidity = msg->isMessageValid(msgt);

    // If the message is valid, meaning that CRC passed and it is for us, therfore parse the message
    if(!msgValidity){
        std::cout << "Received Message is Invalid" << std::endl;
    }
    else{
        msg->parseAircraftMessage(msgt);
    }

    // Print buffer if needed to debug message
//    int len = sizeof(msgt);
//    char *raw = new char[len];
//    memcpy(raw, &msgt, len);
//
//    bitOp::printHex(raw, len);

    // Free message object memory before exiting
    free(msg);
    return 0;
}

