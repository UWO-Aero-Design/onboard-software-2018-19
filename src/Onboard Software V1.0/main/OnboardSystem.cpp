/*
 * File Purpose
 *   Implementing TestSystem.h functions
 */

// For delay and serial
#include "Arduino.h"
#include "Factory.h"
#include "SPI.h"
#include "RH_RF95.h"
#include "Config.h"
#include "OnboardSystem.h"
#include "BitManipulation.h"

// temp
#define CAL_IMU 1
#define CAL_GPS 2
#define CAL_BARO 3
#define PAYLOAD_DROP 1
#define GLIDER_DROP 2

// Only build factory on startup
OnboardSystem::OnboardSystem()
{
	//factory = new Factory();
}

// Clean up objects
OnboardSystem::~OnboardSystem(){
	delete imu;
  delete baro;
  delete gps;
  delete sd;

  delete sb;

  delete rf95;

  delete ledRadio;
  delete ledLoop;
  delete ledError;
}

// Init system
void OnboardSystem::initSystem()
{
  // Create sensor objects
  imu = factory->selectIMU(0);
  baro = factory->selectBaro(0);
  gps = factory->selectGPS(0);
  sd = factory->selectSD(0);
  sb = factory->selectSB(0);

  // Create radio object
  rf95 = new RH_RF95(radio::RFM95_CS, radio::RFM95_INT);

  // Init radio reset pin
  pinMode(radio::RFM95_RST, OUTPUT);
  digitalWrite(radio::RFM95_RST, HIGH);

  // Init serial
  //while (!Serial);
  Serial.begin(9600);
  delay(100);

  // Manual radio reset
  digitalWrite(radio::RFM95_RST, LOW);
  delay(10);
  digitalWrite(radio::RFM95_RST, HIGH);
  delay(10);

  // Init radio
  while (!rf95->init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Default radio settings
  if (!rf95->setFrequency(radio::RFM95_FREQUENCY)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(radio::RFM95_FREQUENCY);

  rf95->setTxPower(radio::RFM95_TX_POWER, false);

  // Init led pins
  ledRadio = new LED(LEDPIN::BLUE_LED,0,0,0);
  ledLoop = new LED(LEDPIN::GREEN_LED,0,0,0);
  ledError = new LED(LEDPIN::RED_LED,0,0,0);
  
  // Initialize IMU objects
  imu->init(-3675, -1303, 611, 73, 50, 14);
  baro->init();
  gps->init();
  sd->init();
  sb->init(8, 16);

  ledRadio->startBlinking(5000, 1000, 50);
  ledError->startBlinking(5000, 1000, 50);
  Serial.print("Ready");
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.println(".\n");
}

void OnboardSystem::updateSystem()
{
  // Update sensors
  imu->update();
  baro->update();
  gps->update();

  // If the radio is available aka something has been sent to us
  if (rf95->available())
  {
    ledRadio->turnOn();
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    
    // Populate message buffer with radio receive function
    if (rf95->recv(buf, &len))
    {
      // Toggle receive led
      

      // Debuggging
      RH_RF95::printBuffer("Received: ", buf, len);
      Serial.print("Got: ");
      Serial.println((char*)buf);
      Serial.print("Received message with RSSI: ");
      Serial.println(rf95->lastRssi(), DEC);

      // Handle request
      msg::ground_to_board_msg_t* incoming_packet = (msg::ground_to_board_msg_t *) buf;
      bool sendResponse = processIncomingPacket(incoming_packet);

      // If the request was for us specifically
      if(sendResponse == true)
      {
        // Build response
        // msg::board_to_ground_msg_t outgoing_packet = {msg::startByte, 
        //                                      0, gps.lat, gps.lon, imu.yaw, imu.pitch, 
        //                                      imu.roll, gps.speed, baro.alt, 0, 0, 0, 
        //                                      gliderDropLat, gliderDropLon, payloadDropLat, payloadDropLon, rssi, errors, 
        //                                      msg::endByte};

        // Default packet for debugging
//        outgoing_packet = {msg::startByte, 
//                                             0, (int32_t)(gps->getLat()*10000000), (int32_t)(gps->getLon()*10000000), imu->getYaw(), 0, 
//                                             0, 0, 0, 0, 0, 0, 
//                                             0, 0, 0, 0, 0, 0, 
//                                             msg::endByte};

        generateRealPacket();
        //printPacket();
        
        // Prepare packet to be sent
        uint8_t data[sizeof(outgoing_packet)];
        memcpy(data, &outgoing_packet, sizeof(outgoing_packet));

        // Send packet
        rf95->send(data, sizeof(data));

        // Turn on send led and wait for packet to send
        rf95->waitPacketSent();
        //Serial.println("Sent a reply");
        ledRadio->turnOff();
      }
    }
    else
    {
      Serial.println("Receive failed");
    }
  }

  ledLoop->turnOn();
	delay(100);
  ledLoop->turnOff();
}

uint8_t OnboardSystem::processIncomingPacket(msg::ground_to_board_msg_t* packet) 
{

  //Serial.println("Processing commands");

  // Enter logic processing down here ...
  // Step 1. Swap order of bits because of struct packing for values greater than 8 bits
  packet->msgType = bit::swapUINT16(packet->msgType);
  packet->targetLat = bit::swapINT32(packet->targetLat);
  packet->targetLon = bit::swapINT32(packet->targetLon);
  packet->motor1 = bit::swapUINT16(packet->motor1);
  packet->motor2 = bit::swapUINT16(packet->motor2);
  packet->motor3 = bit::swapUINT16(packet->motor3);
  packet->motor4 = bit::swapUINT16(packet->motor4);
  packet->motor5 = bit::swapUINT16(packet->motor5);
  packet->motor6 = bit::swapUINT16(packet->motor6);
  packet->motor7 = bit::swapUINT16(packet->motor7);
  packet->motor8 = bit::swapUINT16(packet->motor8);
  packet->motor9 = bit::swapUINT16(packet->motor9);
  packet->motor10 = bit::swapUINT16(packet->motor10);
  packet->motor11 = bit::swapUINT16(packet->motor11);
  packet->motor12 = bit::swapUINT16(packet->motor12);
  packet->motor13 = bit::swapUINT16(packet->motor13);
  packet->motor14 = bit::swapUINT16(packet->motor14);
  packet->motor15 = bit::swapUINT16(packet->motor15);
  packet->motor16 = bit::swapUINT16(packet->motor16);
  packet->error = bit::swapUINT16(packet->error);
  // Check if it is for us. If it is for us, parse appropriately 
  if(packet->msgType == static_cast<uint16_t>(config::sysPlane))
  {
    // Storing target lat and target lon
    targetLat = packet->targetLat/1000000;
    targetLon = packet->targetLon/1000000;
    
    // Calibration request
    switch(packet->calibrate)
    {
      case CAL_IMU:
      {
        // CALIBRATE IMU LOGIC
        Serial.println("Calibrating IMU...");
      }break;

      case CAL_GPS:
      {
        // CALIBRATE GPS LOGIC
        Serial.println("Calibrating GPS...");
      }break;

      case CAL_BARO:
      {
        baro->zero(baro->getSeaLevelPressure());
        // CALIBRATE BARO LOGIC
        Serial.println("Calibrating Barometer...");
      }break;
      default:
      {
        // NOTHING
        Serial.println("Undefined calibrate bit...");
        Serial.print("Value: ");
        Serial.println(packet->calibrate);
      }break;
    }

    // Drop request. Need to handle load/unload
    switch(packet->dropRequest)
    {
      case GLIDER_DROP:
      {
        Serial.println("Glider Drop");
        sendGDrop = true;
        outgoing_packet.gDropLat = gps->getLat()*1000000;
        outgoing_packet.gDropLon = gps->getLon()*1000000;
        openDoors();
        // GLIDER DROP LOGIC with motor controller
        //gliderDropLat = gps.getLat();
        //gliderDropLon = gps.getLon();
      }break;

      case PAYLOAD_DROP:
      {
        Serial.println("Payload Drop");
        sendPDrop = true;
        outgoing_packet.pDropLat = gps->getLat()*1000000;
        outgoing_packet.pDropLon = gps->getLon()*1000000;
        closeDoors();
        // PAYLOAD DROP LOGIC with motor controller
        //payloadDropLat = gps.getLat();
        //payloadDropLon = gps.getLon();
      }break;

      default:
      {
        // NOTHING
      }break;
    }

    // motor request
    if(packet->motor1 == 1) {
      sb->runServo(8, 440);
    }
    else if(packet->motor1 == 2) {
      sb->runServo(8, 440);
    }
    if(packet->motor2 == 1) {
      sb->runServo(8, 440);
    }
    else if(packet->motor2 == 2) {
      sb->runServo(8, 440);
    }
    if(packet->motor3 == 1) {
      sb->runServo(8, 440);
    }
    else if(packet->motor3 == 2) {
      sb->runServo(8, 440);
    }
    if(packet->motor4 == 1) {
      sb->runServo(8, 440);
    }
    else if(packet->motor4 == 2) {
      sb->runServo(8, 440);
    }
    if(packet->motor5 == 1) {
      sb->runServo(8, 440);
    }
    else if(packet->motor5 == 2) {
      sb->runServo(8, 440);
    }
    if(packet->motor6 == 1) {
      sb->runServo(8, 440);
    }
    else if(packet->motor6 == 2) {
      sb->runServo(8, 440);
    }
  }
  else
  {
    // Message was not for us
    // return false;
  }

  // Remove this line after debugging and uncomment return false in else statement
  return true;
}

void OnboardSystem::generateTestPacket(void)
{
   // Test packet 
 outgoing_packet.msgStart = msg::startByte;
 outgoing_packet.msgType = config::sysDebug;
 outgoing_packet.lat += 100;
 outgoing_packet.lon -= 100;
 outgoing_packet.yaw = 0;
 outgoing_packet.pitch = 100;
 outgoing_packet.roll = -100;

 outgoing_packet.speed = 2000;
 outgoing_packet.alt = 10000;

 outgoing_packet.pidYaw = -10;
 outgoing_packet.pidPitch = 0;
 outgoing_packet.pidRoll = 10;

 outgoing_packet.gDropLat = 430110059; 
 outgoing_packet.gDropLon = -812767429;

 outgoing_packet.pDropLat = 435110059; 
 outgoing_packet.pDropLon = -817767429;

 outgoing_packet.rssi = rf95->lastRssi();
 outgoing_packet.error = 20;

 outgoing_packet.msgEnd =  msg::endByte;
}

void OnboardSystem::generateRealPacket()
{
 // Generate real packet
 // Start byte
 outgoing_packet.msgStart = msg::startByte;

 // Message meant for ground station
 outgoing_packet.msgType = 0;

 // Send back current latitude and longitude 
 outgoing_packet.lat = (gps->getLat()) * 1000000;
 outgoing_packet.lon = (gps->getLon()) * 1000000;

 if(sendGDrop) sendGDrop = false;
 else {
  outgoing_packet.gDropLat = 0;
  outgoing_packet.gDropLon = 0;
 }
 if(sendPDrop) sendPDrop = false;
 else {
  outgoing_packet.pDropLat = 0;
  outgoing_packet.pDropLon = 0;
 }

 // Send back current yaw, pitch, roll
 outgoing_packet.yaw = imu->getYaw() * 100;
 outgoing_packet.pitch = imu->getPitch() * 100;
 outgoing_packet.roll = imu->getRoll() * 100;

 // Send back speed, altitude
 outgoing_packet.speed = gps->getSpeed();
 outgoing_packet.alt = gps->getAlt();

 // Send back RSSI
 outgoing_packet.rssi = rf95->lastRssi();

 // End byte
 outgoing_packet.msgEnd =  msg::endByte;


 /* THE REST OF THE BYTES ARE SENT ASYNCHRONOUSLY, MEANING ONLY WHEN THEY ARE REQUESTED */
}

void OnboardSystem::printPacket()
{
 Serial.print("Message Type: ");
 Serial.println(outgoing_packet.msgType);
 
 Serial.print("Lat: ");
 Serial.println((double)outgoing_packet.lat / 10000000);
 Serial.print("Lon: ");
 Serial.println((double)outgoing_packet.lon / 10000000);
 
 Serial.print("Yaw: ");
 Serial.println((double)outgoing_packet.yaw / 100);
 Serial.print("Pitch: ");
 Serial.println((double)outgoing_packet.pitch / 100);
 Serial.print("Roll: ");
 Serial.println((double)outgoing_packet.roll / 100);
 
 Serial.print("Speed: ");
 Serial.println(outgoing_packet.speed);
 Serial.print("Alt: ");
 Serial.println(outgoing_packet.alt);

 Serial.print("gDropLat: ");
 Serial.println((double)outgoing_packet.gDropLat / 10000000);
 Serial.print("gDropLon: ");
 Serial.println((double)outgoing_packet.gDropLon / 10000000);
 Serial.print("pDropLat: ");
 Serial.println((double)outgoing_packet.pDropLat / 10000000);
 Serial.print("pDropLon: ");
 Serial.println((double)outgoing_packet.pDropLon / 10000000);
 
 Serial.print("rssi: ");
 Serial.println(outgoing_packet.rssi);
 
 Serial.print("error: ");
 Serial.println(outgoing_packet.error);
}


bool OnboardSystem::openDoors() {
  sb->runServo(8, 440);
  return sb->isError();
}

bool OnboardSystem::closeDoors() {
  sb->runServo(8, 180);
  return sb->isError();
}

bool OnboardSystem::dropPayload() {
  sb->runServo(9, 0);
  return sb->isError();
}

bool OnboardSystem::dropGlider() {
  sb->runServo(9, 180);
  return sb->isError();
}
