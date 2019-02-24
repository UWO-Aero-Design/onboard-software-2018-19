// //
// // Created by cbaro on 2018-11-30.
// //

// #include "Arduino.h"
// #include "Message.h"
// #include "BitManipulation.h"

// Message::Message() {
// }
// Message::~Message(){
// }

// // TODO(Carl Baron: Jan 10th, 2019): 
// msg::message_t Message::buildMessage(uint8_t recipient, msg::aircraft_message_t data) {
//     // Message to be sent
//     msg::message_t message;

//     // Set start byte
//     message.packet.msgStart = msg::startByte;

//     // Set start type based on who we are and the recipient
//     message.packet.msgType = buildMessageType(recipient);

//     // Set the data ID based on the fields selected
//     message.packet.dataID = 0;
//     message.packet.buf = new char[sizeof(data)];
//     memcpy(message.packet.buf, &data, sizeof(data));
   
//     // Build the end bytes
//     message.packet.msgEnd = msg::endByte;

//     //TODO: Calculate CRC
//     message.checksum = generateCRC(message.packet);

//     return message;
// }

// // Building message type based on recipient and who we are
// uint16_t Message::buildMessageType(uint8_t recipient) {
//     uint8_t topHalf = config::thisSystem;
//     uint8_t bottomHalf = recipient;

//     uint16_t msgType = ((uint16_t)topHalf << 8) | bottomHalf;
//     return msgType;
// }


// // // TODO: add data extraction method. Thinking that we pass a reference to an object. Maybe replace struct with an object to abstract away the process?
// // void Message::parseAircraftMessage(msg::message_t msg){

// //     uint16_t dataID = msg.packet.dataID;

// //     // Separate into a new function, just need to pass the char *buf and maybe return the data inside
// //     int dataIndex = 0;
// //     if(bit::readBit(dataID, msg::airLat)){
// //         int32_t lat = 0;
// //         memcpy(&lat,msg.packet.buf + dataIndex,sizeof(lat));
// //         dataIndex += sizeof(lat);
// //     }

// //     if(bit::readBit(dataID, msg::airLon)){
// //         int32_t lon = 0;
// //         memcpy(&lon,msg.packet.buf + dataIndex,sizeof(lon));
// //         dataIndex += sizeof(lon);
// //     }

// //     if(bit::readBit(dataID, msg::airYaw)){
// //         int16_t yaw = 0;
// //         memcpy(&yaw,msg.packet.buf + dataIndex,sizeof(yaw));
// //         dataIndex += sizeof(yaw);
// //     }

// //     if(bit::readBit(dataID, msg::airPitch)){
// //         int16_t pitch = 0;
// //         memcpy(&pitch,msg.packet.buf + dataIndex,sizeof(pitch));
// //         dataIndex += sizeof(pitch);
// //     }


// //     if(bit::readBit(dataID, msg::airRoll)){
// //         int16_t roll = 0;
// //         memcpy(&roll,msg.packet.buf + dataIndex,sizeof(roll));
// //         dataIndex += sizeof(roll);
// //     }

// //     if(bit::readBit(dataID, msg::airSpeed)){
// //         uint16_t speed = 0;
// //         memcpy(&speed,msg.packet.buf + dataIndex,sizeof(speed));
// //         dataIndex += sizeof(speed);
// //     }

// //     if(bit::readBit(dataID, msg::airAltitude)){
// //         uint16_t alt = 0;
// //         memcpy(&alt,msg.packet.buf + dataIndex,sizeof(alt));
// //         dataIndex += sizeof(alt);
// //     }

// //     if(bit::readBit(dataID, msg::airPIDYaw)){
// //         int16_t pidYaw = 0;
// //         memcpy(&pidYaw,msg.packet.buf + dataIndex,sizeof(pidYaw));
// //         dataIndex += sizeof(pidYaw);
// //     }

// //     if(bit::readBit(dataID, msg::airPIDPitch)){
// //         int16_t pidPitch = 0;
// //         memcpy(&pidPitch,msg.packet.buf + dataIndex,sizeof(pidPitch));
// //         dataIndex += sizeof(pidPitch);
// //     }


// //     if(bit::readBit(dataID, msg::airPIDRoll)){
// //         int16_t pidRoll = 0;
// //         memcpy(&pidRoll,msg.packet.buf + dataIndex,sizeof(pidRoll));
// //         dataIndex += sizeof(pidRoll);
// //     }

// //     if(bit::readBit(dataID, msg::airDropLat)){
// //         int32_t dropLat = 0;
// //         memcpy(&dropLat,msg.packet.buf + dataIndex,sizeof(dropLat));
// //         dataIndex += sizeof(dropLat);
// //     }

// //     if(bit::readBit(dataID, msg::airDropLon)){
// //         int32_t dropLon = 0;
// //         memcpy(&dropLon,msg.packet.buf + dataIndex,sizeof(dropLon));
// //         dataIndex += sizeof(dropLon);
// //     }

// //     if(bit::readBit(dataID, msg::airRSSI)){
// //         uint8_t rssi = 0;
// //         memcpy(&rssi,msg.packet.buf + dataIndex,sizeof(rssi));
// //         dataIndex += sizeof(rssi);
// //     }

// //     if(bit::readBit(dataID, msg::airErrorCode)){
// //         uint16_t error = 0;
// //         memcpy(&error,msg.packet.buf + dataIndex,sizeof(error));
// //     }
// // }

// // // TODO: add data extraction method. Thinking that we pass a reference to an object. Maybe replace struct with an object to abstract away the process?
// // void Message::parseGroundStationMessage(msg::message_t msg){

// //     uint16_t dataID = msg.packet.dataID;

// //     int dataIndex = 0;
// //     if(bit::readBit(dataID, msg::gndTargetLat)){
// //         int32_t targetLat = 0;
// //         memcpy(&targetLat, msg.packet.buf + dataIndex, sizeof(targetLat));
// //         dataIndex += sizeof(targetLat);
// //     }

// //     if(bit::readBit(dataID, msg::gndTargetLon)){
// //         int32_t targetLon = 0;
// //         memcpy(&targetLon, msg.packet.buf + dataIndex, sizeof(targetLon));
// //         dataIndex += sizeof(targetLon);
// //     }

// //     if(bit::readBit(dataID, msg::gndCalibrate)){
// //         uint8_t calibrate = 0;
// //         memcpy(&calibrate, msg.packet.buf + dataIndex, sizeof(calibrate));
// //         dataIndex += sizeof(calibrate);
// //     }

// //     if(bit::readBit(dataID, msg::gndRSSI)){
// //         uint8_t rssi = 0;
// //         memcpy(&rssi, msg.packet.buf + dataIndex, sizeof(rssi));
// //         dataIndex += sizeof(rssi);
// //     }

// //     if(bit::readBit(dataID, msg::gndDropRequest)){
// //         uint8_t dropRequest = 0;
// //         memcpy(&dropRequest, msg.packet.buf + dataIndex, sizeof(dropRequest));
// //         dataIndex += sizeof(dropRequest);
// //     }

// //     if(bit::readBit(dataID, msg::gndGliders)){
// //         uint8_t gliders = 0;
// //         memcpy(&gliders, msg.packet.buf + dataIndex,sizeof(gliders));
// //         dataIndex += sizeof(gliders);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor1)){
// //         uint8_t motor1 = 0;
// //         memcpy(&motor1, msg.packet.buf + dataIndex,sizeof(motor1));
// //         dataIndex += sizeof(motor1);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor2)){
// //         uint8_t motor2 = 0;
// //         memcpy(&motor2, msg.packet.buf + dataIndex,sizeof(motor2));
// //         dataIndex += sizeof(motor2);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor3)){
// //         uint8_t motor3 = 0;
// //         memcpy(&motor3, msg.packet.buf + dataIndex,sizeof(motor3));
// //         dataIndex += sizeof(motor3);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor4)){
// //         uint8_t motor4 = 0;
// //         memcpy(&motor4, msg.packet.buf + dataIndex,sizeof(motor4));
// //         dataIndex += sizeof(motor4);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor5)){
// //         uint8_t motor5 = 0;
// //         memcpy(&motor5, msg.packet.buf + dataIndex,sizeof(motor5));
// //         dataIndex += sizeof(motor5);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor6)){
// //         uint8_t motor6 = 0;
// //         memcpy(&motor6, msg.packet.buf + dataIndex,sizeof(motor6));
// //         dataIndex += sizeof(motor6);
// //     }       

// //     if(bit::readBit(dataID, msg::gndMotor7)){
// //         uint8_t motor7 = 0;
// //         memcpy(&motor7, msg.packet.buf + dataIndex,sizeof(motor7));
// //         dataIndex += sizeof(motor7);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor8)){
// //         uint8_t motor8 = 0;
// //         memcpy(&motor8, msg.packet.buf + dataIndex,sizeof(motor8));
// //         dataIndex += sizeof(motor8);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor9)){
// //         uint8_t motor9 = 0;
// //         memcpy(&motor9, msg.packet.buf + dataIndex,sizeof(motor9));
// //         dataIndex += sizeof(motor9);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor10)){
// //         uint8_t motor10 = 0;
// //         memcpy(&motor10, msg.packet.buf + dataIndex,sizeof(motor10));
// //         dataIndex += sizeof(motor10);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor11)){
// //         uint8_t motor11 = 0;
// //         memcpy(&motor11, msg.packet.buf + dataIndex,sizeof(motor11));
// //         dataIndex += sizeof(motor11);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor12)){
// //         uint8_t motor12 = 0;
// //         memcpy(&motor12, msg.packet.buf + dataIndex,sizeof(motor12));
// //         dataIndex += sizeof(motor12);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor13)){
// //         uint8_t motor13 = 0;
// //         memcpy(&motor13, msg.packet.buf + dataIndex,sizeof(motor13));
// //         dataIndex += sizeof(motor13);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor14)){
// //         uint8_t motor14 = 0;
// //         memcpy(&motor14, msg.packet.buf + dataIndex,sizeof(motor14));
// //         dataIndex += sizeof(motor14);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor15)){
// //         uint8_t motor15 = 0;
// //         memcpy(&motor15, msg.packet.buf + dataIndex,sizeof(motor15));
// //         dataIndex += sizeof(motor15);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor16)){
// //         uint8_t motor16 = 0;
// //         memcpy(&motor16, msg.packet.buf + dataIndex,sizeof(motor16));
// //         dataIndex += sizeof(motor16);
// //     }

// //     if(bit::readBit(dataID, msg::gndMotor16)){
// //         uint8_t error = 0;
// //         memcpy(&error, msg.packet.buf + dataIndex,sizeof(error));
// //     }

// // }

// // TODO: Change to error codes for precise debugging
// // bool Message::isMessageValid(msg::message_t msg){

// //     //TODO: ADD CRC
// //     bool crcResult = crcCheck(msg.packet, msg.checksum);

// //     // CRC failed
// //     if(!crcResult){
// //         return false;
// //     }

// //     // Check who it was from and see if it is for us
// //     // TODO(Carl Baron: Jan 10th, 2019): Change from reading uint8_t to uint16_t
// //     uint8_t msgType = msg.packet.msgType;
// //     uint8_t fromWho = bit::readUpperByteNibble(msgType);
// //     uint8_t forWho  = bit::readLowerByteNibble(msgType);

// //     // Dont parse message if we receive a message that is not meant for us
// //     if(forWho != config::thisSystem){
// //         return false;
// //     }else{
// //         // If we get here, the CRC passed, and the message is for us
// //         return true;
// //     }
// // }

// bool Message::crcCheck(msg::unsecuredData_t packet, uint8_t checksum){
//     // if message.checksum != message checksummed
    
//     // TODO. for now return true, but dont always do that
//     return true;
// }

// uint8_t Message::generateCRC(msg::unsecuredData_t packet){
//     // TODO use packet to generate a checksum value
//     uint8_t checksum = 0xFF;
//     return checksum;
// }




