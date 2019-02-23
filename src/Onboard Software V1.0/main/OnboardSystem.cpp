/*
 * File Purpose
 *   Implementing TestSystem.h functions
 */

// For delay and serial
#include "Arduino.h"

#include "Factory.h"

#include "SPI.h"
#include "RH_RF95.h"

OnboardSystem::OnboardSystem()
{
	factory = new Factory();
}

OnboardSystem::~OnboardSystem(){
	// Empty	
}

void OnboardSystem::initSystem()
{
  imu = factory->selectIMU(0);
  baro = factory->selectBaro(0);
  gps = factory->selectGPS(0);
  sd = factory->selectSD(0);

  rf95 = new RH_RF95();
  rf95->setTxPower(23, false);
  
  imu->init(-3675, -1303, 611, 73, 50, 14);
  baro->init();
  gps->init();
  sd->init();
}

void OnboardSystem::updateSystem()
{
  imu->update();
  baro->update();
  gps->update();


  if (rf95.available())
  {
    if (rf95.recv(buf, &len))
    {
      //      RH_RF95::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
      //      Serial.print("RSSI: ");
      //      Serial.println(rf95.lastRssi(), DEC);
      
      // Send a reply
      //uint8_t data[] = "And hello back to you";

      // Build message with struct

      // PARSE MESSAGE( BUF )

      char* data = ...;
      uint8_t msgLen = sizeof(msg);
      rf95.send(data, sizeof(data));

      rf95.waitPacketSent();
      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
  }

  //Serial.println(gps->getSatellites());

  
 
	delay(100);
}
