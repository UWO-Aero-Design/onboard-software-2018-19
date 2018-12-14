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

msg::message_t Message::buildMessage(msg::aircraft_bits dataFields, uint8_t recipient, void* data) {
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

    // Build buffer depending on who we are sending too
    if(recipient == config::sysGndStation){
        message.packet.buf = buildGroundstationMessageBuffer(dataFields, data);
    }else{
        message.packet.buf = buildGroundstationMessageBuffer(dataFields, data);
    }
   
    // Build the end bytes
    message.packet.msgEnd = msg::endByte;

    //TODO: Calculate CRC
    message.checksum = generateCRC(message.packet);

    return message;
}

// Building message type based on recipient and who we are
uint16_t Message::buildMessageType(uint8_t recipient) {
    uint8_t topHalf = config::thisSystem;
    uint8_t bottomHalf = recipient;

    uint16_t msgType = ((uint16_t)topHalf << 8) | bottomHalf;
    return msgType;
}

// TODO: Change to error codes for precise debugging
bool Message::isMessageValid(msg::message_t msg){

    //TODO: ADD CRC
    bool crcResult = crcCheck(msg.packet, msg.checksum);

    // CRC failed
    if(!crcResult){
        return false;
    }

    // Check who it was from and see if it is for us
    uint8_t msgType = msg.packet.msgType;
    uint8_t fromWho = bitOp::readUpperByteNibble(msgType);
    uint8_t forWho  = bitOp::readLowerByteNibble(msgType);

    // Dont parse message if we receive a message that is not meant for us
    if(forWho != thisSystem){
        return false;
    }else{
        // If we get here, the CRC passed, and the message is for us
        return true;
    }
}

bool Message::crcCheck(unsecuredData_t packet, uint8_t checksum){
    // if message.checksum != message checksummed
    
    // TODO. for now return true, but dont always do that
    return true;
}

uint8_t Message::generateCRC(unsecuredData_t packet){
    // TODO use packet to generate a checksum value
    uint8_t checksum = 0xFF;
    return checksum;
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

// TODO: add data extraction method. Thinking that we pass a reference to an object. Maybe replace struct with an object to abstract away the process?
void Message::parseAircraftMessage(msg::message_t msg){

    uint16_t dataID = msg.packet.dataID;

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
}

// TODO: add data extraction method. Thinking that we pass a reference to an object. Maybe replace struct with an object to abstract away the process?
void Message::parseGroundStationMessage(msg::message_t msg){

    uint16_t dataID = msg.packet.dataID;

    int dataIndex = 0;
    if(bitOp::readBit(dataID, msg::gndTargetLat)){
        int32_t targetLat = 0;
        memcpy(&targetLat, msg.packet.buf + dataIndex, sizeof(targetLat));
        dataIndex += sizeof(targetLat);
    }

    if(bitOp::readBit(dataID, msg::gndTargetLon)){
        int32_t targetLon = 0;
        memcpy(&targetLon, msg.packet.buf + dataIndex, sizeof(targetLon));
        dataIndex += sizeof(targetLon);
    }

    if(bitOp::readBit(dataID, msg::gndCalibrate)){
        uint8_t calibrate = 0;
        memcpy(&calibrate, msg.packet.buf + dataIndex, sizeof(calibrate));
        dataIndex += sizeof(calibrate);
    }

    if(bitOp::readBit(dataID, msg::gndRSSI)){
        uint8_t rssi = 0;
        memcpy(&rssi, msg.packet.buf + dataIndex, sizeof(rssi));
        dataIndex += sizeof(rssi);
    }

    if(bitOp::readBit(dataID, msg::gndDropRequest)){
        uint8_t dropRequest = 0;
        memcpy(&dropRequest, msg.packet.buf + dataIndex, sizeof(dropRequest));
        dataIndex += sizeof(dropRequest);
    }

    if(bitOp::readBit(dataID, msg::gndGliders)){
        uint8_t gliders = 0;
        memcpy(&gliders, msg.packet.buf + dataIndex,sizeof(gliders));
        dataIndex += sizeof(gliders);
    }

    if(bitOp::readBit(dataID, msg::gndMotor1)){
        uint8_t motor1 = 0;
        memcpy(&motor1, msg.packet.buf + dataIndex,sizeof(motor1));
        dataIndex += sizeof(motor1);
    }

    if(bitOp::readBit(dataID, msg::gndMotor2)){
        uint8_t motor2 = 0;
        memcpy(&motor2, msg.packet.buf + dataIndex,sizeof(motor2));
        dataIndex += sizeof(motor2);
    }

    if(bitOp::readBit(dataID, msg::gndMotor3)){
        uint8_t motor3 = 0;
        memcpy(&motor3, msg.packet.buf + dataIndex,sizeof(motor3));
        dataIndex += sizeof(motor3);
    }

    if(bitOp::readBit(dataID, msg::gndMotor4)){
        uint8_t motor4 = 0;
        memcpy(&motor4, msg.packet.buf + dataIndex,sizeof(motor4));
        dataIndex += sizeof(motor4);
    }

    if(bitOp::readBit(dataID, msg::gndMotor5)){
        uint8_t motor5 = 0;
        memcpy(&motor5, msg.packet.buf + dataIndex,sizeof(motor5));
        dataIndex += sizeof(motor5);
    }

    if(bitOp::readBit(dataID, msg::gndMotor6)){
        uint8_t motor6 = 0;
        memcpy(&motor6, msg.packet.buf + dataIndex,sizeof(motor6));
        dataIndex += sizeof(motor6);
    }       

    if(bitOp::readBit(dataID, msg::gndMotor7)){
        uint8_t motor7 = 0;
        memcpy(&motor7, msg.packet.buf + dataIndex,sizeof(motor7));
        dataIndex += sizeof(motor7);
    }

    if(bitOp::readBit(dataID, msg::gndMotor8)){
        uint8_t motor8 = 0;
        memcpy(&motor8, msg.packet.buf + dataIndex,sizeof(motor8));
        dataIndex += sizeof(motor8);
    }

    if(bitOp::readBit(dataID, msg::gndMotor9)){
        uint8_t motor9 = 0;
        memcpy(&motor9, msg.packet.buf + dataIndex,sizeof(motor9));
        dataIndex += sizeof(motor9);
    }

    if(bitOp::readBit(dataID, msg::gndMotor10)){
        uint8_t motor10 = 0;
        memcpy(&motor10, msg.packet.buf + dataIndex,sizeof(motor10));
        dataIndex += sizeof(motor10);
    }

    if(bitOp::readBit(dataID, msg::gndMotor11)){
        uint8_t motor11 = 0;
        memcpy(&motor11, msg.packet.buf + dataIndex,sizeof(motor11));
        dataIndex += sizeof(motor11);
    }

    if(bitOp::readBit(dataID, msg::gndMotor12)){
        uint8_t motor12 = 0;
        memcpy(&motor12, msg.packet.buf + dataIndex,sizeof(motor12));
        dataIndex += sizeof(motor12);
    }

    if(bitOp::readBit(dataID, msg::gndMotor13)){
        uint8_t motor13 = 0;
        memcpy(&motor13, msg.packet.buf + dataIndex,sizeof(motor13));
        dataIndex += sizeof(motor13);
    }

    if(bitOp::readBit(dataID, msg::gndMotor14)){
        uint8_t motor14 = 0;
        memcpy(&motor14, msg.packet.buf + dataIndex,sizeof(motor14));
        dataIndex += sizeof(motor14);
    }

    if(bitOp::readBit(dataID, msg::gndMotor15)){
        uint8_t motor15 = 0;
        memcpy(&motor15, msg.packet.buf + dataIndex,sizeof(motor15));
        dataIndex += sizeof(motor15);
    }

    if(bitOp::readBit(dataID, msg::gndMotor16)){
        uint8_t motor16 = 0;
        memcpy(&motor16, msg.packet.buf + dataIndex,sizeof(motor16));
        dataIndex += sizeof(motor16);
    }

    if(bitOp::readBit(dataID, msg::gndMotor16)){
        uint8_t error = 0;
        memcpy(&error, msg.packet.buf + dataIndex,sizeof(error));
    }

}


