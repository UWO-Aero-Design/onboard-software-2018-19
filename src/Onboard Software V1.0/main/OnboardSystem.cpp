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
	//delete imu;
  //delete baro;
  //delete gps;

  delete rf95;

  delete ledReceived;
  delete ledSent;
}

// Init system
void OnboardSystem::initSystem()
{
  // Create sensor objects
  //imu = factory->selectIMU(0);
  //baro = factory->selectBaro(0);
  //gps = factory->selectGPS(0);
  // sd = factory->selectSD(0);

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
  ledReceived = new LED(LEDPIN::BLUE_LED,0,0,0);
  ledSent = new LED(LEDPIN::YELLOW_LED,0,0,0);
  
  // Initialize IMU objects
  //imu->init(-3675, -1303, 611, 73, 50, 14);
  //baro->init();
  //gps->init();
  //sd->init();
}

void OnboardSystem::updateSystem()
{
  // Update sensors
  //imu->update();
  //baro->update();
  //gps->update();

  // If the radio is available aka something has been sent to us
  if (rf95->available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    
    // Populate message buffer with radio receive function
    if (rf95->recv(buf, &len))
    {
      // Toggle receive led
      ledReceived->turnOn();

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
        ledSent->turnOn();
        rf95->waitPacketSent();
        Serial.println("Sent a reply");
      }

      // Turn off leds
      ledSent->turnOff();
      ledReceived->turnOff();
    }
    else
    {
      Serial.println("Receive failed");
    }
  }

	delay(100);
}

bool OnboardSystem::processIncomingPacket(msg::ground_to_board_msg_t* packet) 
{

  // TODO: NEED TO SWAP ENDIANS AFTER RECEIVING PACKETS

  Serial.println("Processing commands");
  // Enter logic processing down here ... 

  Serial.print("Msg start: ");
  Serial.println(packet->msgStart);
  
  Serial.print("Msg type: ");
  Serial.println(packet->msgType);

    Serial.print("targetLat: ");
  Serial.println(bit::swapINT32(packet->targetLat));

    Serial.print("targetLon: ");
  Serial.println(bit::swapINT32(packet->targetLon));

    Serial.print("calibrate: ");
  Serial.println(packet->calibrate);

    Serial.print("rssi: ");
  Serial.println(packet->rssi);

    Serial.print("dropRequest: ");
  Serial.println(packet->dropRequest);

    Serial.print("gliders: ");
  Serial.println(packet->gliders);

    Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor1));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor2));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor3));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor4));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor5));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor6));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor7));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor8));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor9));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor10));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor11));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor12));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor13));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor14));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor15));
      Serial.print("Motor: ");
  Serial.println(bit::swapUINT16(packet->motor16));


          Serial.print("Error: ");
  Serial.println(packet->error);

          Serial.print("End: ");
  Serial.println(packet->msgEnd);
    
  // Check if it is for us. If it is for us, parse appropriately 
  if(packet->msgType == static_cast<uint16_t>(config::sysPlane))
  {

    
    // Calibration request
    switch(packet->calibrate)
    {
      case CAL_IMU:
      {
        // CALIBRATE IMU LOGIC
      }break;

      case CAL_GPS:
      {
        // CALIBRATE GPS LOGIC
      }break;

      case CAL_BARO:
      {
        // CALIBRATE BARO LOGIC
      }break;
      default:
      {
        // NOTHING
      }break;
    }

    // Drop request
    switch(packet->dropRequest)
    {
      case GLIDER_DROP:
      {
        // GLIDER DROP LOGIC with motor controller
      }break;

      case PAYLOAD_DROP:
      {
        // PAYLOAD DROP LOGIC with motor controller
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
