//
// Created by cbaro on 2018-11-30.
//

#include <cstring>
#include <iostream>
#include "Message.h"
#include "Data.h"

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

    // TODO: Need correct buffer size
    // Build the data buffer
    message.packet.buf = new char[1000];

    // TODO: Select correct message builder based on recipient
    message.packet.buf = buildAircraftMessageBuffer(dataFields, data);

    // Build the end bytes
    message.packet.msgEnd = msg::endByte;

    //TODO: Calculate CRC
    message.checksum = 0xFF;

    return message;
}

// First nibble of the byte is who we are, second nibble is who we are sending to
uint8_t Message::buildMessageType(uint8_t recipient) {
    uint8_t msgType = 0;
    msgType = bitOp::setUpperByteNibble(msgType, config::thisSystem);
    msgType = bitOp::setLowerByteNibble(msgType, recipient);
    
    // For debugging
    std::cout << "Msg Type Debug: " << msgType << std::endl;
}


// Welcome to the absolute laziest way of preparing the data buffer for the message protocol
// If the bit for a specific data field is set, copy that data element into the buffer
char* Message::buildAircraftMessageBuffer(msg::aircraft_bits dataFields, void* data){
    // Initialize data index to keep track of our position in the buffer
    int dataIndex = 0;

    msg::aircraft_message_t* aircraft = (msg::aircraft_message_t *)(data);
    // TODO: Need to extract size from data fields and not from struct cause struct is max size
    char* buf = new char[sizeof(aircraft)];

    // If Lat bit was set, copy lat into the buffer
    if(bitOp::readBit(dataFields, msg::airLat)){
        memcpy(buf + dataIndex, &aircraft->lat, sizeof(aircraft->lat));
        dataIndex += sizeof(aircraft->lat);
    }

    // If Lon bit was set, copy lon into the buffer
    if(bitOp::readBit(dataFields, msg::airLon)){
        memcpy(buf + dataIndex, &aircraft->lon, sizeof(aircraft->lon));
        dataIndex += sizeof(aircraft->lon);
    }

    // If Yaw bit was set, copy yaw into the buffer
    if(bitOp::readBit(dataFields, msg::airYaw)){
        memcpy(buf + dataIndex, &aircraft->yaw, sizeof(aircraft->yaw));
        dataIndex += sizeof(aircraft->yaw);
    }

    // If Pitch bit was set, copy pitch into the buffer
    if(bitOp::readBit(dataFields, msg::airPitch)){
        memcpy(buf + dataIndex, &aircraft->pitch, sizeof(aircraft->pitch));
        dataIndex += sizeof(aircraft->pitch);
    }

    // If Roll bit was set, copy roll into the buffer
    if(bitOp::readBit(dataFields, msg::airRoll)){
        memcpy(buf + dataIndex, &aircraft->roll, sizeof(aircraft->roll));
        dataIndex += sizeof(aircraft->roll);
    }

    // If Speed bit was set, copy speed into the buffer
    if(bitOp::readBit(dataFields, msg::airSpeed)){
        memcpy(buf + dataIndex, &aircraft->speed, sizeof(aircraft->speed));
        dataIndex += sizeof(aircraft->speed);
    }

    // If Altitude bit was set, copy alt into the buffer
    if(bitOp::readBit(dataFields, msg::airAltitude)){
        memcpy(buf + dataIndex, &aircraft->alt, sizeof(aircraft->alt));
        dataIndex += sizeof(aircraft->alt);
    }

    // If PID Yaw bit was set, copy pid yaw into the buffer
    if(bitOp::readBit(dataFields, msg::airPIDYaw)){
        memcpy(buf + dataIndex, &aircraft->pidYaw, sizeof(aircraft->pidYaw));
        dataIndex += sizeof(aircraft->pidYaw);
    }

    // If PID pitch bit was set, copy pid pitch into the buffer
    if(bitOp::readBit(dataFields, msg::airPIDPitch)){
        memcpy(buf + dataIndex, &aircraft->pidPitch, sizeof(aircraft->pidPitch));
        dataIndex += sizeof(aircraft->pidPitch);
    }

    // If PID roll bit was set, copy pid roll into the buffer
    if(bitOp::readBit(dataFields, msg::airPIDRoll)){
        memcpy(buf + dataIndex, &aircraft->pidRoll, sizeof(aircraft->pidRoll));
        dataIndex += sizeof(aircraft->pidRoll);
    }

    // If Drop Lat bit was set, copy drop lat into the buffer
    if(bitOp::readBit(dataFields, msg::airDropLat)){
        memcpy(buf + dataIndex, &aircraft->dropLat, sizeof(aircraft->dropLat));
        dataIndex += sizeof(aircraft->dropLat);
    }

    // If Drop Lon bit was set, copy drop lon into the buffer
    if(bitOp::readBit(dataFields, msg::airDropLon)){
        memcpy(buf + dataIndex, &aircraft->dropLon, sizeof(aircraft->dropLon));
        dataIndex += sizeof(aircraft->dropLon);
    }

    // If RSSI bit was set, copy rssi into the buffer
    if(bitOp::readBit(dataFields, msg::airRSSI)){
        memcpy(buf + dataIndex, &aircraft->rssi, sizeof(aircraft->rssi));
        dataIndex += sizeof(aircraft->rssi);
    }

    // If Error Code bit was set, copy errors into the buffer
    if(bitOp::readBit(dataFields, msg::airErrorCode)){
        memcpy(buf + dataIndex, &aircraft->error, sizeof(aircraft->error));
        // Do not need to update data index because this will always be the last element in the buf
    }

    return buf;
}

// Welcome to the absolute laziest way of preparing the data buffer for the message protocol
// If the bit for a specific data field is set, copy that data element into the buffer
char* Message::buildGroundstationMessageBuffer(msg::gnd_station_bits dataFields, void* data){
    // Initialize data index to keep track of our position in the buffer
    int dataIndex = 0;

    msg::gnd_station_message_t* gnd_station = (msg::gnd_station_message_t *)(data);

    // TODO: Need to extract size from data fields and not from struct cause struct is max size
    char* buf = new char[sizeof(gnd_station)];

    // If Target lat bit was set, copy Target lat into the buffer
    if(bitOp::readBit(dataFields, msg::gndTargetLat)){
        memcpy(buf + dataIndex, &gnd_station->targetLat, sizeof(gnd_station->targetLat));
        dataIndex += sizeof(gnd_station->targetLat);
    }

    // If Target lon bit was set, copy Target lon into the buffer
    if(bitOp::readBit(dataFields, msg::gndTargetLon)){
        memcpy(buf + dataIndex, &gnd_station->targetLon, sizeof(gnd_station->targetLon));
        dataIndex += sizeof(gnd_station->targetLon);
    }

    // If Calibrate bit was set, copy Calibrate flags into the buffer
    if(bitOp::readBit(dataFields, msg::gndCalibrate)){
        memcpy(buf + dataIndex, &gnd_station->calibrate, sizeof(gnd_station->calibrate));
        dataIndex += sizeof(gnd_station->calibrate);
    }

    // If RSSI bit was set, copy RSSI into the buffer
    if(bitOp::readBit(dataFields, msg::gndRSSI)){
        memcpy(buf + dataIndex, &gnd_station->rssi, sizeof(gnd_station->rssi));
        dataIndex += sizeof(gnd_station->rssi);
    }

    // If Drop Request bit was set, copy Drop Request flags into the buffer
    if(bitOp::readBit(dataFields, msg::gndDropRequest)){
        memcpy(buf + dataIndex, &gnd_station->dropRequest, sizeof(gnd_station->dropRequest));
        dataIndex += sizeof(gnd_station->dropRequest);
    }

    // If Gliders bit was set, copy Glider flags into the buffer
    if(bitOp::readBit(dataFields, msg::gndGliders)){
        memcpy(buf + dataIndex, &gnd_station->gliders, sizeof(gnd_station->gliders));
        dataIndex += sizeof(gnd_station->gliders);
    }

    // If Motors 1 bit was set, copy Motor 1 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor1)){
        memcpy(buf + dataIndex, &gnd_station->motor1, sizeof(gnd_station->motor1));
        dataIndex += sizeof(gnd_station->motor1);
    }

    // If Motors 2 bit was set, copy Motor 2 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor2)){
        memcpy(buf + dataIndex, &gnd_station->motor2, sizeof(gnd_station->motor2));
        dataIndex += sizeof(gnd_station->motor2);
    }

    // If Motors 3 bit was set, copy Motor 3 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor3)){
        memcpy(buf + dataIndex, &gnd_station->motor3, sizeof(gnd_station->motor3));
        dataIndex += sizeof(gnd_station->motor3);
    }

    // If Motors 4 bit was set, copy Motor 4 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor4)){
        memcpy(buf + dataIndex, &gnd_station->motor4, sizeof(gnd_station->motor4));
        dataIndex += sizeof(gnd_station->motor4);
    }

    // If Motors 5 bit was set, copy Motor 5 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor5)){
        memcpy(buf + dataIndex, &gnd_station->motor5, sizeof(gnd_station->motor5));
        dataIndex += sizeof(gnd_station->motor5);
    }

    // If Motors 6 bit was set, copy Motor 6 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor6)){
        memcpy(buf + dataIndex, &gnd_station->motor6, sizeof(gnd_station->motor6));
        dataIndex += sizeof(gnd_station->motor6);
    }

    // If Motors 7 bit was set, copy Motor 7 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor7)){
        memcpy(buf + dataIndex, &gnd_station->motor7, sizeof(gnd_station->motor7));
        dataIndex += sizeof(gnd_station->motor7);
    }

    // If Motors 8 bit was set, copy Motor 8 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor8)){
        memcpy(buf + dataIndex, &gnd_station->motor8, sizeof(gnd_station->motor8));
        dataIndex += sizeof(gnd_station->motor8);
    }

    // If Motors 9 bit was set, copy Motor 9 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor9)){
        memcpy(buf + dataIndex, &gnd_station->motor9, sizeof(gnd_station->motor9));
        dataIndex += sizeof(gnd_station->motor9);
    }

    // If Motors 10 bit was set, copy Motor 10 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor10)){
        memcpy(buf + dataIndex, &gnd_station->motor10, sizeof(gnd_station->motor10));
        dataIndex += sizeof(gnd_station->motor10);
    }

    // If Motors 11 bit was set, copy Motor 11 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor11)){
        memcpy(buf + dataIndex, &gnd_station->motor11, sizeof(gnd_station->motor11));
        dataIndex += sizeof(gnd_station->motor11);
    }

    // If Motors 12 bit was set, copy Motor 12 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor12)){
        memcpy(buf + dataIndex, &gnd_station->motor12, sizeof(gnd_station->motor12));
        dataIndex += sizeof(gnd_station->motor12);
    }

    // If Motors 13 bit was set, copy Motor 13 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor13)){
        memcpy(buf + dataIndex, &gnd_station->motor13, sizeof(gnd_station->motor13));
        dataIndex += sizeof(gnd_station->motor13);
    }

    // If Motors 14 bit was set, copy Motor 14 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor14)){
        memcpy(buf + dataIndex, &gnd_station->motor14, sizeof(gnd_station->motor14));
        dataIndex += sizeof(gnd_station->motor14);
    }

    // If Motors 15 bit was set, copy Motor 15 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor15)){
        memcpy(buf + dataIndex, &gnd_station->motor15, sizeof(gnd_station->motor15));
        dataIndex += sizeof(gnd_station->motor15);
    }
    
    // If Motors 16 bit was set, copy Motor 16 command into the buffer
    if(bitOp::readBit(dataFields, msg::gndMotor16)){
        memcpy(buf + dataIndex, &gnd_station->motor16, sizeof(gnd_station->motor16));
        dataIndex += sizeof(gnd_station->motor16);
    }

    // If Error bit was set, copy Error status into the buffer
    if(bitOp::readBit(dataFields, msg::gndErrorCode)){
        memcpy(buf + dataIndex, &gnd_station->error, sizeof(gnd_station->error));
    }

    return buf;
}

void Message::parseMessage(msg::message_t msg){

    // First check CRC. If CRC failed, break from function
    uint16_t dataID = msg.packet.dataID;

    // Check who it was from and see if it is for us
    uint8_t msgType = msg.packet.msgType;
    uint8_t fromWho = bitOp::readUpperByteNibble(msgType);
    uint8_t forWho  = bitOp::readLowerByteNibble(msgType);

    // Dont parse message if we receive a message that is not meant for us
    if(forWho != thisSystem){
        return;
    }

    // TODO: Separate parsing based on who we received the message from
    if(fromWho == config::sysGndStation){
        // parse GndStation
    }else{
        // parse Aircraft
        // Need to know who sent it though, maybe include that in the struct that is passed to us?
    }

    // Separate into a new function, just need to pass the char *buf and maybe return the data inside
    int dataIndex = 0;
    if(bitOp::readBit(dataID, msg::airLat)){
        int32_t lat = 0;
        memcpy(&lat,msg.packet.buf + dataIndex,sizeof(lat));
        dataIndex += sizeof(lat);
    }

    if(bitOp::readBit(dataID, msg::airLon)){
        int32_t lon = 0;
        memcpy(&lon,msg.packet.buf + dataIndex,sizeof(lon));
        dataIndex += sizeof(lon);
        std::cout << lon;
    }

    if(bitOp::readBit(dataID, msg::airYaw)){
        int16_t yaw = 0;
        memcpy(&yaw,msg.packet.buf + dataIndex,sizeof(yaw));
        dataIndex += sizeof(yaw);
    }

    if(bitOp::readBit(dataID, msg::airPitch)){
        int16_t pitch = 0;
        memcpy(&pitch,msg.packet.buf + dataIndex,sizeof(pitch));
        dataIndex += sizeof(pitch);
    }


    if(bitOp::readBit(dataID, msg::airRoll)){
        int16_t roll = 0;
        memcpy(&roll,msg.packet.buf + dataIndex,sizeof(roll));
        dataIndex += sizeof(roll);
    }

    if(bitOp::readBit(dataID, msg::airSpeed)){
        uint16_t speed = 0;
        memcpy(&speed,msg.packet.buf + dataIndex,sizeof(speed));
        dataIndex += sizeof(speed);
    }

    if(bitOp::readBit(dataID, msg::airAltitude)){
        uint16_t alt = 0;
        memcpy(&alt,msg.packet.buf + dataIndex,sizeof(alt));
        dataIndex += sizeof(alt);
    }

    if(bitOp::readBit(dataID, msg::airPIDYaw)){
        int16_t pidYaw = 0;
        memcpy(&pidYaw,msg.packet.buf + dataIndex,sizeof(pidYaw));
        dataIndex += sizeof(pidYaw);
    }

    if(bitOp::readBit(dataID, msg::airPIDPitch)){
        int16_t pidPitch = 0;
        memcpy(&pidPitch,msg.packet.buf + dataIndex,sizeof(pidPitch));
        dataIndex += sizeof(pidPitch);
    }


    if(bitOp::readBit(dataID, msg::airPIDRoll)){
        int16_t pidRoll = 0;
        memcpy(&pidRoll,msg.packet.buf + dataIndex,sizeof(pidRoll));
        dataIndex += sizeof(pidRoll);
    }

    if(bitOp::readBit(dataID, msg::airDropLat)){
        int32_t dropLat = 0;
        memcpy(&dropLat,msg.packet.buf + dataIndex,sizeof(dropLat));
        dataIndex += sizeof(dropLat);
    }

    if(bitOp::readBit(dataID, msg::airDropLon)){
        int32_t dropLon = 0;
        memcpy(&dropLon,msg.packet.buf + dataIndex,sizeof(dropLon));
        dataIndex += sizeof(dropLon);
    }

    if(bitOp::readBit(dataID, msg::airRSSI)){
        uint8_t rssi = 0;
        memcpy(&rssi,msg.packet.buf + dataIndex,sizeof(rssi));
        dataIndex += sizeof(rssi);
    }

    if(bitOp::readBit(dataID, msg::airErrorCode)){
        uint16_t error = 0;
        memcpy(&error,msg.packet.buf + dataIndex,sizeof(error));
    }

    // End byte is only used for telling the Bluetooth to stop reading in data, not for parsing

}
