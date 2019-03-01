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
#define CAL_IMU 0
#define CAL_GPS 1
#define CAL_BARO 2
#define PAYLOAD_DROP 0
#define GLIDER_DROP 1

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
  while (!Serial);
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
  
  // Initialize IMU objects
  imu->init(-3675, -1303, 611, 73, 50, 14);
  baro->init();
  gps->init();
  sd->init();
  sb->init(8, 16);
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
        msg::board_to_ground_msg_t outgoing_packet = {msg::startByte, 
                                             0, 0, 0, 0, 0, 
                                             0, 0, 0, 0, 0, 0, 
                                             0, 0, 0, 0, 0, 0, 
                                             msg::endByte};
        
        // Prepare packet to be sent
        uint8_t data[sizeof(outgoing_packet)];
        memcpy(data, &outgoing_packet, sizeof(outgoing_packet));

        // Send packet
        rf95->send(data, sizeof(data));

        // Turn on send led and wait for packet to send
        rf95->waitPacketSent();
        Serial.println("Sent a reply");
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

bool OnboardSystem::processIncomingPacket(msg::ground_to_board_msg_t* packet) 
{

  Serial.println("Processing commands");

  // Enter logic processing down here ...
  // Step 1. Swap order of bits because of struct packing for values greater than 8 bits
  packet->msgType = bit::swapUINT16(packet->msgType);
  packet->targetLat = bit::swapINT32(packet->targetLat);
  packet->targetLon = bit::swapINT32(packet->targetLon);
  packet->motor1 = bit::swapUINT16(packet->motor1);
  packet->motor1 = bit::swapUINT16(packet->motor2);
  packet->motor1 = bit::swapUINT16(packet->motor3);
  packet->motor1 = bit::swapUINT16(packet->motor4);
  packet->motor1 = bit::swapUINT16(packet->motor5);
  packet->motor1 = bit::swapUINT16(packet->motor6);
  packet->motor1 = bit::swapUINT16(packet->motor7);
  packet->motor1 = bit::swapUINT16(packet->motor8);
  packet->motor1 = bit::swapUINT16(packet->motor9);
  packet->motor1 = bit::swapUINT16(packet->motor10);
  packet->motor1 = bit::swapUINT16(packet->motor11);
  packet->motor1 = bit::swapUINT16(packet->motor12);
  packet->motor1 = bit::swapUINT16(packet->motor13);
  packet->motor1 = bit::swapUINT16(packet->motor14);
  packet->motor1 = bit::swapUINT16(packet->motor15);
  packet->motor1 = bit::swapUINT16(packet->motor16);
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
        // GLIDER DROP LOGIC with motor controller
        //gliderDropLat = gps.getLat();
        //gliderDropLon = gps.getLon();
      }break;

      case PAYLOAD_DROP:
      {
        // PAYLOAD DROP LOGIC with motor controller
        //payloadDropLat = gps.getLat();
        //payloadDropLon = gps.getLon();
      }break;

      default:
      {
        // NOTHING
      }break;
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


bool OnboardSystem::openDoors() {
  sb->runServo(0, 0);
  return sb->isError();
}

bool OnboardSystem::closeDoors() {
  sb->runServo(0, 0);
  return sb->isError();
}

bool OnboardSystem::dropPayload() {
  sb->runServo(0, 0);
  return sb->isError();
}

bool OnboardSystem::dropGlider() {
  sb->runServo(0, 0);
  return sb->isError();
}
