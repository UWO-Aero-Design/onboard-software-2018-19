#include "SoftwareSerial.h"
#include "GroundstationSystem.h"
// #include "Message.h"

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
  // Buffer setup
  //bleBuffer = new char[100];
  bufferFilled = false;

  // Init radio reset pin
  pinMode(radio::RFM95_RST, OUTPUT);
  digitalWrite(radio::RFM95_RST, HIGH);

  //Init serial
  while (!Serial);
  Serial.begin(9600);
  delay(100);

  // Objects
  //myPort = new SoftwareSerial(10,11);
  //myPort->begin(9600);
  Serial4.begin(9600);
  
  bluetooth = new HC05(myPort); 
  rf95 = new RH_RF95(radio::RFM95_CS, radio::RFM95_INT);

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
  Serial.print("GND. Set Freq to: "); Serial.println(radio::RFM95_FREQUENCY);
  
  // Set power
  rf95->setTxPower(radio::RFM95_TX_POWER, false);

}

// The ground station acts as a server, constantly sending out messages
// The plane then decides how to respond
void Groundstation::updateSystem()
{
    // add port available wrap to hc05 class? 
    if(Serial4.available())
    {
        // bleBuffer = bluetooth->performStringRead();
        // if(!(bleBuffer[0] = 0x00))
        // {
        //     bufferFilled = true;
        // }

        // testing to see if messages route to other board over radio
        // String copy for this operation?
        bleBuffer = (char)Serial4.read();
        Serial.println(bleBuffer);
        bufferFilled = true;
    }

    if(bufferFilled)
    {
        Serial.println("Sending..."); delay(10);
        char test[2];
        test[0] = bleBuffer;
        test[1] = 0;
        rf95->send((uint8_t *) test, sizeof(test));

        Serial.println("Waiting for packet to complete..."); 
        delay(10);
        rf95->waitPacketSent();

        // Now wait for a reply
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        Serial.println("Waiting for reply..."); delay(10);
        if (rf95->waitAvailableTimeout(1000))
        { 
            // Should be a reply message for us now   
            if (rf95->recv(buf, &len))
            {
                Serial.print("Got reply: ");
                Serial.println((char*)buf);
                Serial.print("RSSI: ");
                Serial.println(rf95->lastRssi(), DEC); 

                Serial4.write((char*)buf);
            }
            else
            {
                Serial.println("Receive failed");
            }
        }
        else
        {
            Serial.println("No reply, is there a listener around?");
        }

    delay(RADIO_MSG_RATE_MS);

    }
}
