//
// Created by cbaro on 2018-11-30.
//

#include <cstring>
#include <iostream>
#include "Message.h"

Message::Message() {
}
Message::~Message(){
}

msg::message_t Message::buildMessage(msg::aircraft_bits dataFields, uint8_t dataBufSize, uint8_t recipient, void* data) {
    // Message to be sent
    msg::message_t message;

    // Set start byte
    message.packet.msgStart = msg::startByte;

    // Set start type based on who we are and the recipient

    message.packet.msgType = buildMessageType(recipient);

    // Set the data ID based on the fields selected
    message.packet.dataID = (uint16_t ) dataFields;

    // Build the data buffer
    message.packet.buf = new char[1000];
    message.packet.buf = buildMessageBuf(dataFields, data);

    // Build the end bytes
    message.packet.msgEnd = msg::endByte;

    //message.checksum = calcCRC();
    message.checksum = 0xFF;

    return message;
}

// First nibble of the byte is who we are, second nibble is who we are sending to
uint16_t Message::buildMessageType(uint8_t recipient) {
    return 0x0B;
}


// Welcome to the absolute laziest way of preparing the data buffer for the message protocol
// If the bit for a specific data field is set, copy that data element into the buffer
char* Message::buildMessageBuf(msg::aircraft_bits dataFields, void* data){
    // Initialize data index to keep track of our position in the buffer
    int dataIndex = 0;

    msg::aircraft_message_t* air = (msg::aircraft_message_t *)(data);

    // Data fields. Will be populated by a struct later
    int32_t lat, lon, dropLat, dropLon;
    int16_t yaw, pitch, roll, pidYaw, pidPitch, pidRoll;
    uint16_t speed, alt, error;
    uint8_t rssi;

    char* buf = new char[sizeof(air)];

    // If Lat bit was set, copy lat into the buffer
    if(bitOp::readBit(dataFields, msg::bLat)){
        memcpy(buf + dataIndex, &lat, sizeof(lat));
        dataIndex += sizeof(lat);
    }

    // If Lon bit was set, copy lon into the buffer
    if(bitOp::readBit(dataFields, msg::bLon)){
        memcpy(buf + dataIndex, &air->lon, sizeof(air->lon));
        dataIndex += sizeof(air->lon);
    }

    // If Yaw bit was set, copy yaw into the buffer
    if(bitOp::readBit(dataFields, msg::bYaw)){
        memcpy(buf + dataIndex, &yaw, sizeof(yaw));
        dataIndex += sizeof(yaw);
    }

    // If Pitch bit was set, copy pitch into the buffer
    if(bitOp::readBit(dataFields, msg::bPitch)){
        memcpy(buf + dataIndex, &pitch, sizeof(pitch));
        dataIndex += sizeof(pitch);
    }

    // If Roll bit was set, copy roll into the buffer
    if(bitOp::readBit(dataFields, msg::bRoll)){
        memcpy(buf + dataIndex, &roll, sizeof(roll));
        dataIndex += sizeof(roll);
    }

    // If Speed bit was set, copy speed into the buffer
    if(bitOp::readBit(dataFields, msg::bSpeed)){
        memcpy(buf + dataIndex, &speed, sizeof(speed));
        dataIndex += sizeof(speed);
    }

    // If Altitude bit was set, copy alt into the buffer
    if(bitOp::readBit(dataFields, msg::bAltitude)){
        memcpy(buf + dataIndex, &alt, sizeof(alt));
        dataIndex += sizeof(alt);
    }

    // If PID Yaw bit was set, copy pid yaw into the buffer
    if(bitOp::readBit(dataFields, msg::bPIDYaw)){
        memcpy(buf + dataIndex, &pidYaw, sizeof(pidYaw));
        dataIndex += sizeof(pidYaw);
    }

    // If PID pitch bit was set, copy pid pitch into the buffer
    if(bitOp::readBit(dataFields, msg::bPIDPitch)){
        memcpy(buf + dataIndex, &pidPitch, sizeof(pidPitch));
        dataIndex += sizeof(pidPitch);
    }

    // If PID roll bit was set, copy pid roll into the buffer
    if(bitOp::readBit(dataFields, msg::bPIDRoll)){
        memcpy(buf + dataIndex, &pidRoll, sizeof(pidRoll));
        dataIndex += sizeof(pidRoll);
    }

    // If Drop Lat bit was set, copy drop lat into the buffer
    if(bitOp::readBit(dataFields, msg::bDropLat)){
        memcpy(buf + dataIndex, &dropLat, sizeof(dropLat));
        dataIndex += sizeof(dropLat);
    }

    // If Drop Lon bit was set, copy drop lon into the buffer
    if(bitOp::readBit(dataFields, msg::bDropLon)){
        memcpy(buf + dataIndex, &dropLon, sizeof(dropLon));
        dataIndex += sizeof(dropLon);
    }

    // If RSSI bit was set, copy rssi into the buffer
    if(bitOp::readBit(dataFields, msg::bRSSI)){
        memcpy(buf + dataIndex, &rssi, sizeof(rssi));
        dataIndex += sizeof(rssi);
    }

    // If Error Code bit was set, copy errors into the buffer
    if(bitOp::readBit(dataFields, msg::bErrorCode)){
        memcpy(buf + dataIndex, &error, sizeof(error));
    }

    return buf;

}

void Message::parseMessage(msg::message_t msg){

    // First check CRC. If CRC failed, break from function
    uint16_t dataID = msg.packet.dataID;

    // Separate into a new function, just need to pass the char *buf and maybe return the data inside
    int dataIndex = 0;
    if(bitOp::readBit(dataID, msg::bLat)){
        int32_t lat = 0;
        memcpy(&lat,msg.packet.buf + dataIndex,sizeof(lat));
        dataIndex += sizeof(lat);
    }

    if(bitOp::readBit(dataID, msg::bLon)){
        int32_t lon = 0;
        memcpy(&lon,msg.packet.buf + dataIndex,sizeof(lon));
        dataIndex += sizeof(lon);
        std::cout << lon;
    }

    if(bitOp::readBit(dataID, msg::bYaw)){
        int16_t yaw = 0;
        memcpy(&yaw,msg.packet.buf + dataIndex,sizeof(yaw));
        dataIndex += sizeof(yaw);
    }

    if(bitOp::readBit(dataID, msg::bPitch)){
        int16_t pitch = 0;
        memcpy(&pitch,msg.packet.buf + dataIndex,sizeof(pitch));
        dataIndex += sizeof(pitch);
    }


    if(bitOp::readBit(dataID, msg::bRoll)){
        int16_t roll = 0;
        memcpy(&roll,msg.packet.buf + dataIndex,sizeof(roll));
        dataIndex += sizeof(roll);
    }

    if(bitOp::readBit(dataID, msg::bSpeed)){
        uint16_t speed = 0;
        memcpy(&speed,msg.packet.buf + dataIndex,sizeof(speed));
        dataIndex += sizeof(speed);
    }

    if(bitOp::readBit(dataID, msg::bAltitude)){
        uint16_t alt = 0;
        memcpy(&alt,msg.packet.buf + dataIndex,sizeof(alt));
        dataIndex += sizeof(alt);
    }

    if(bitOp::readBit(dataID, msg::bPIDYaw)){
        int16_t pidYaw = 0;
        memcpy(&pidYaw,msg.packet.buf + dataIndex,sizeof(pidYaw));
        dataIndex += sizeof(pidYaw);
    }

    if(bitOp::readBit(dataID, msg::bPIDPitch)){
        int16_t pidPitch = 0;
        memcpy(&pidPitch,msg.packet.buf + dataIndex,sizeof(pidPitch));
        dataIndex += sizeof(pidPitch);
    }


    if(bitOp::readBit(dataID, msg::bPIDRoll)){
        int16_t pidRoll = 0;
        memcpy(&pidRoll,msg.packet.buf + dataIndex,sizeof(pidRoll));
        dataIndex += sizeof(pidRoll);
    }

    if(bitOp::readBit(dataID, msg::bDropLat)){
        int32_t dropLat = 0;
        memcpy(&dropLat,msg.packet.buf + dataIndex,sizeof(dropLat));
        dataIndex += sizeof(dropLat);
    }

    if(bitOp::readBit(dataID, msg::bDropLon)){
        int32_t dropLon = 0;
        memcpy(&dropLon,msg.packet.buf + dataIndex,sizeof(dropLon));
        dataIndex += sizeof(dropLon);
    }

    if(bitOp::readBit(dataID, msg::bRSSI)){
        uint8_t rssi = 0;
        memcpy(&rssi,msg.packet.buf + dataIndex,sizeof(rssi));
        dataIndex += sizeof(rssi);
    }

    if(bitOp::readBit(dataID, msg::bErrorCode)){
        uint16_t error = 0;
        memcpy(&error,msg.packet.buf + dataIndex,sizeof(error));
    }

    // End byte is only used for telling the Bluetooth to stop reading in data, not for parsing

}
