///*
// * File Purpose
// *   Implementing TestSystem.h functions
// */
//
//// For delay and serial
//#include "Arduino.h"
//#include "Factory.h"
//#include "SPI.h"
//#include "RH_RF95.h"
//#include "Config.h"
//#include "OnboardSystem.h"
//#include "BitManipulation.h"
//
//// temp
//#define CAL_IMU 0
//#define CAL_GPS 1
//#define CAL_BARO 2
//#define PAYLOAD_DROP 0
//#define GLIDER_DROP 1
//
//// Only build factory on startup
//OnboardSystem::OnboardSystem()
//{
//	//factory = new Factory();
//}
//
//// Clean up objects
//OnboardSystem::~OnboardSystem(){
//	delete imu;
//  delete baro;
//  delete gps;
//  delete sd;
//
//  delete sb;
//
//  delete rf95;
//
//  delete ledRadio;
//  delete ledLoop;
//}
//
//// Init system
//void OnboardSystem::initSystem()
//{
//  // For debugging
//  outgoing_packet.lat = 430110059; 
//  outgoing_packet.lon = -812767429;
//
//  // Initialize struct to 0 for to avoid undefined behavior
//  outgoing_packet.pidYaw = 0;
//  outgoing_packet.pidPitch = 0;
//  outgoing_packet.pidRoll = 0;
//  outgoing_packet.gDropLat = 0;
//  outgoing_packet.gDropLon = 0;
//  outgoing_packet.pDropLat = 0;
//  outgoing_packet.pDropLon = 0;
//  outgoing_packet.error = 0;
//
//  // Create sensor objects
//  imu = factory->selectIMU(0);
//  baro = factory->selectBaro(0);
//  gps = factory->selectGPS(0);
//  sd = factory->selectSD(0);
//  sb = factory->selectSB(0);
//
//  // Create radio object
//  rf95 = new RH_RF95(radio::RFM95_CS, radio::RFM95_INT);
//
//  // Init radio reset pin
//  pinMode(radio::RFM95_RST, OUTPUT);
//  digitalWrite(radio::RFM95_RST, HIGH);
//
//   //Init serial. Happens in main?
//   while (!Serial);
//   Serial.begin(9600);
//   delay(100);
//
//  // Manual radio reset
//  digitalWrite(radio::RFM95_RST, LOW);
//  delay(10);
//  digitalWrite(radio::RFM95_RST, HIGH);
//  delay(10);
//
//  // Init radio
//  while (!rf95->init()) {
//    Serial.println("LoRa radio init failed");
//    while (1);
//  }
//  Serial.println("LoRa radio init OK!");
//
//  // Default radio settings
//  if (!rf95->setFrequency(radio::RFM95_FREQUENCY)) {
//    Serial.println("setFrequency failed");
//    while (1);
//  }
//  Serial.print("Set Freq to: "); Serial.println(radio::RFM95_FREQUENCY);
//
//  rf95->setTxPower(radio::RFM95_TX_POWER, false);
//
//  // Init led pins
//  ledRadio = new LED(LEDPIN::BLUE_LED,0,0,0);
//  ledLoop = new LED(LEDPIN::GREEN_LED,0,0,0);
//  ledError = new LED(LEDPIN::RED_LED,0,0,0);
//  
//  // Initialize IMU objects
//  imu->init(-3675, -1303, 611, 73, 50, 14);
//  baro->init();
//  gps->init();
//  sd->init();
//  sb->init(8, 16);
//
//  // Play boot sequence so we know which board we are in  
//  ledError->startBlinking(5000,1000,50);
//  ledRadio->startBlinking(5000,1000,50);
//  delay(5000);
//
//}
//
//void OnboardSystem::updateSystem()
//{
//  // Update sensors
//  imu->update();
//  baro->update();
//  gps->update();
//
//  // If the radio is available aka something has been sent to us
//  if (rf95->available())
//  {
//    ledRadio->turnOn();
//    // Should be a message for us now   
//    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
//    uint8_t len = sizeof(buf);
//    
//    // Populate message buffer with radio receive function
//    if (rf95->recv(buf, &len))
//    {
//      // Debuggging
//      RH_RF95::printBuffer("Received: ", buf, len);
//      Serial.print("Got: ");
//      Serial.println((char*)buf);
//      Serial.print("Received message with RSSI: ");
//      Serial.println(rf95->lastRssi(), DEC);
//
//      // Handle request
		// Move incoming packet to class variable 
//      msg::ground_to_board_msg_t* incoming_packet = (msg::ground_to_board_msg_t *) buf;
//      uint8_t responseCode = processIncomingPacket(incoming_packet);
//
//      // If the message request is accepted
//      if(responseCode > 0)
//      {
//        // If the message request was from an aircraft
//        if(responseCode != static_cast<uint16_t>(config::sysDebug))
//        {
//          generateRealPacket();
//        }
//        else  // Message was for requesting a debug message
//        {
//          generateTestPacket();
//        }
//
//        // Prepare packet to be sent
//        uint8_t data[sizeof(outgoing_packet)];
//        memcpy(data, &outgoing_packet, sizeof(outgoing_packet));
//
//        // Send packet
//        rf95->send(data, sizeof(data));
//
//        // Turn on send led and wait for packet to send
//        rf95->waitPacketSent();
//        Serial.println("Sent a reply");
//        outgoing_packet.error = 0;
//        ledRadio->turnOff();
//      }
//      else
//      {
//        // Radio is available and receive worked but request code was invalid
//        Serial.println("Request error");
//        ledError->startBlinking(5000, 100, 50);
//        outgoing_packet.error |= 1;
//      }
//    }
//    else
//    {
//      // Radio is available but receive failed
//      Serial.println("Receive failed");
//      ledError->startBlinking(10000, 500, 50);
//      outgoing_packet.error |= 2;
//    }
//  }
//  else
//  {
//    // Radio unavailable
//    // Serial.println("Radio unavailable");
//  }
//
//  ledLoop->startBlinking(50, 50, 100);
//	delay(100);
//}
//
//uint8_t OnboardSystem::processIncomingPacket(msg::ground_to_board_msg_t* packet) 
//{
//
//  Serial.println("Processing commands");
//
//  // Enter logic processing down here ...
//  // Step 1. Swap order of bits because of struct packing for values greater than 8 bits
//  packet->msgType = bit::swapUINT16(packet->msgType);
//  packet->targetLat = bit::swapINT32(packet->targetLat);
//  packet->targetLon = bit::swapINT32(packet->targetLon);
//  packet->motor1 = bit::swapUINT16(packet->motor1);
//  packet->motor1 = bit::swapUINT16(packet->motor2);
//  packet->motor1 = bit::swapUINT16(packet->motor3);
//  packet->motor1 = bit::swapUINT16(packet->motor4);
//  packet->motor1 = bit::swapUINT16(packet->motor5);
//  packet->motor1 = bit::swapUINT16(packet->motor6);
//  packet->motor1 = bit::swapUINT16(packet->motor7);
//  packet->motor1 = bit::swapUINT16(packet->motor8);
//  packet->motor1 = bit::swapUINT16(packet->motor9);
//  packet->motor1 = bit::swapUINT16(packet->motor10);
//  packet->motor1 = bit::swapUINT16(packet->motor11);
//  packet->motor1 = bit::swapUINT16(packet->motor12);
//  packet->motor1 = bit::swapUINT16(packet->motor13);
//  packet->motor1 = bit::swapUINT16(packet->motor14);
//  packet->motor1 = bit::swapUINT16(packet->motor15);
//  packet->motor1 = bit::swapUINT16(packet->motor16);
//  packet->error = bit::swapUINT16(packet->error);
//  
//  if(packet->msgType == static_cast<uint16_t>(config::sysDebug))
//  {
//    return static_cast<uint16_t>(config::sysDebug);
//  }
//
//
//  // Check if it is for us. If it is for us, parse appropriately 
//  if(packet->msgType == static_cast<uint16_t>(config::sysPlane))
//  {
//    // Storing target lat and target lon
//    targetLat = packet->targetLat/1000000;
//    targetLon = packet->targetLon/1000000;
//    
//    // Calibration request
//    switch(packet->calibrate)
//    {
//      case CAL_IMU:
//      {
//        // CALIBRATE IMU LOGIC
//        Serial.println("Calibrating IMU...");
//      }break;
//
//      case CAL_GPS:
//      {
//        // CALIBRATE GPS LOGIC
//        Serial.println("Calibrating GPS...");
//      }break;
//
//      case CAL_BARO:
//      {
//        // CALIBRATE BARO LOGIC
//        Serial.println("Calibrating Barometer...");
//      }break;
//      default:
//      {
//        // NOTHING
//        Serial.println("Undefined calibrate bit...");
//        Serial.print("Value: ");
//        Serial.println(packet->calibrate);
//      }break;
//    }
//
//    // Drop request. Need to handle load/unload
//    switch(packet->dropRequest)
//    {
//      case GLIDER_DROP:
//      {
//        // GLIDER DROP LOGIC with motor controller
//        outgoing_packet.gDropLat = gps->getLat()*1000000;
//        outgoing_packet.gDropLon = gps->getLon()*1000000;
//      }break;
//
//      case PAYLOAD_DROP:
//      {
//        // PAYLOAD DROP LOGIC with motor controller
//        outgoing_packet.pDropLat = gps->getLat()*1000000;
//        outgoing_packet.pDropLon = gps->getLon()*1000000;
//      }break;
//
//      default:
//      {
//        // NOTHING
//      }break;
//    }
//  }
//  else
//  {
//    // Message was not for us
//    // return false;
//  }
//
//  // Remove this line after debugging and uncomment return false in else statement
//  return 1;
//}
//
//void OnboardSystem::generateTestPacket(void)
//{
//    // Test packet 
//  outgoing_packet.msgStart = msg::startByte;
//  outgoing_packet.msgType = config::sysDebug;
//  outgoing_packet.lat += 100;
//  outgoing_packet.lon -= 100;
//  outgoing_packet.yaw = 0;
//  outgoing_packet.pitch = 100;
//  outgoing_packet.roll = -100;
//
//  outgoing_packet.speed = 2000;
//  outgoing_packet.alt = 10000;
//
//  outgoing_packet.pidYaw = -10;
//  outgoing_packet.pidPitch = 0;
//  outgoing_packet.pidRoll = 10;
//
//  outgoing_packet.gDropLat = 430110059; 
//  outgoing_packet.gDropLon = -812767429;
//
//  outgoing_packet.pDropLat = 435110059; 
//  outgoing_packet.pDropLon = -817767429;
//
//  outgoing_packet.rssi = rf95->lastRssi();
//  outgoing_packet.error = 20;
//
//  outgoing_packet.msgEnd =  msg::endByte;
//}
//
//void OnboardSystem::generateRealPacket()
//{
//  // Generate real packet
//  // Start byte
//  outgoing_packet.msgStart = msg::startByte;
//
//  // Message meant for ground station
//  outgoing_packet.msgType = config::sysGndStation;
//
//  // Send back current latitude and longitude 
//  outgoing_packet.lat = (gps->getLat()) * 1000000;
//  outgoing_packet.lon = (gps->getLon()) * 1000000;
//
//  // Send back current yaw, pitch, roll
//  outgoing_packet.yaw = imu->getYaw();
//  outgoing_packet.pitch = imu->getPitch();
//  outgoing_packet.roll = imu->getRoll();
//
//  // Send back speed, altitude
//  outgoing_packet.speed = gps->getSpeed();
//  outgoing_packet.alt = gps->getAlt();
//
//  // Send back RSSI
//  outgoing_packet.rssi = rf95->lastRssi();
//
//  // End byte
//  outgoing_packet.msgEnd =  msg::endByte;
//
//  /* THE REST OF THE BYTES ARE SENT ASYNCHRONOUSLY, MEANING ONLY WHEN THEY ARE REQUESTED */
//}
//
//
//bool OnboardSystem::openDoors() {
//  sb->runServo(0, 0);
//  return sb->isError();
//}
//
//bool OnboardSystem::closeDoors() {
//  sb->runServo(0, 0);
//  return sb->isError();
//}
//
//bool OnboardSystem::dropPayload() {
//  sb->runServo(0, 0);
//  return sb->isError();
//}
//
//bool OnboardSystem::dropGlider() {
//  sb->runServo(0, 0);
//  return sb->isError();
//}
