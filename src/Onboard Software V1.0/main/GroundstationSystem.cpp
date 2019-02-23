#include "SoftwareSerial.h"
#include "GroundstationSystem.h"
#include "Message.h"

#include "SPI.h"
#include "RH_RF95.h"

Groundstation::Groundstation()
{
	// do nothing
};

Groundstation::~Groundstation()
{
	delete bluetooth;
	delete myPort;
  delete rf95;
};

void Groundstation::initSystem()
{
  myPort = new SoftwareSerial(10,11);
  bluetooth = new HC05(myPort); 
  rf95 = new RH_RF95();

  rf->setTxPower(23, false);
}

// The ground station acts as a server, constantly sending out messages
// The plane then decides how to respond
void Groundstation::updateSystem()
{
  Serial.println("Starting ground station update loop...");

  // Wait for new msg
  char* fromTabletMsg = bluetooth->performStringRead();
  uint8_t msgLen = sizeof(fromTabletMsg)

  // After blocking hc05 processor gets new msg, send it off over radio
  rf95.send((uint8_t *)data, sizeof(data));

  // Wait for response
  if (rf95.waitAvailableTimeout(3000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
    {
      // Send reply from plane or groundstation to tablet
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      bluetooth->performStringWrite((char*)buf)
      //      Serial.print("RSSI: ");
      //      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf95_server running?");
  }

  bluetooth->performByteWrite(c);
  bluetooth->performStringWrite(cc);
  delay(100); 
}
