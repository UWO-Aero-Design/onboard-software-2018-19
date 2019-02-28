#include "SoftwareSerial.h"
#include "GroundstationSystem.h"
// #include "Message.h"

#include "SPI.h"
#include "RH_RF95.h"

Groundstation::Groundstation()
{
	// do nothing
  Serial.println("GROUND STATION SYSTEM SELECTED");
};

Groundstation::~Groundstation()
{
  // Turn off all LEDS before destruction
  ledBluetooth->turnOff();
  ledRadio->turnOff();
  ledLoop->turnOff();

  // Free all memory
  delete rf95;
  delete ledBluetooth;
  delete ledRadio;
  delete ledLoop;
};

// Initialize the system
void Groundstation::initSystem()
{
  Serial.println("Initialization ground station system...");

  // Init radio reset pin
  pinMode(radio::RFM95_RST, OUTPUT);
  digitalWrite(radio::RFM95_RST, HIGH);

  //Init serial
  while (!Serial);
  Serial.begin(9600);
  delay(100);

  // Objects
  Serial4.begin(9600);
  rf95 = new RH_RF95(radio::RFM95_CS, radio::RFM95_INT);
  ledBluetooth = new LED(LEDPIN::YELLOW_LED,0,0,0);
  ledRadio = new LED(LEDPIN::BLUE_LED,0,0,0);
  ledLoop = new LED(LEDPIN::GREEN_LED,0,0,0);

  // Setup up bluetooth buffer variables
  started = false;
  ended = false;
  index = 0;
  bufferFilled = false;

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

  // Setting the radio frequency to 915 MHz
  Serial.print("Set Freq to: "); Serial.println(radio::RFM95_FREQUENCY);
  
  // Set power to maximum
  rf95->setTxPower(radio::RFM95_TX_POWER, false);

}

// The ground station acts as a server, constantly sending out messages
// The plane then decides how to respond
void Groundstation::updateSystem()
{
  // Read in bluetooth if available
  while(Serial4.available())
  {

    ledBluetooth->turnOn();

    // Read in a single input byte
    char in = Serial4.read();
    Serial.println((uint8_t)in);

    // If the input byte is the start byte, and we havent already received the start byte, reset the buffer and store the first byte
    if(in == _start && started == false)
    {
      index = 0;
      _buffer[index] = (uint8_t) in;

      Serial.print("Index: ");
      Serial.print(index);
      Serial.print(" Start: ");
      Serial.println((uint8_t)_buffer[index]);

      started = true;
      ended = false;
    }
    // If the input byte is the end byte, end the bufer
    else if(in == _end)
    {
      _buffer[index] = in;

      Serial.print("Index: ");
      Serial.print(index);
      Serial.print(" End: ");
      Serial.println((uint8_t)_buffer[index]);

      ended = true;
    }
    // If the byte is between start and end, increment the index and add it to the buffer
    else if(started == true)
    {
      if(index < (buffersize - 1))
      {
        _buffer[++index] = in;

        Serial.print("Index: ");
        Serial.print(index);
        Serial.print(" Else: ");
        Serial.println((uint8_t)_buffer[index]);
      }
    }

    // If we have hit both the start and end bytes, message is fully recevied
    if(started && ended){
      // Buffer is full
      bufferFilled = true;

      // Reset flags and index and fail counter
      started = false;
      ended = false;
      index = 0;
      fails = 0;

      Serial.println("Bluetooth message read");
    }
    else{
      // Number of fails should not exceed size of message. If it does, then we have a problem
      fails++;
    }
  }

  // If the buffer has been filled, start sending data over radio to onboard
  if(bufferFilled)
  {
      // Send the struct over
      ledRadio->turnOn();
      Serial.println("Sending..."); delay(10);

      // Printing buffer for debugging
      for(int i = 0; i < sizeof(_buffer); ++i)
      {
        Serial.print(" ");
        Serial.print((uint8_t)_buffer[i]);
      }
      
      Serial.println("");
      rf95->send((uint8_t *) _buffer, sizeof(msg::ground_to_board_msg_t));

      // Wait for succesful package delivery
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
              ledRadio->turnOff();

              // Send response to tablet over bluetooth
              Serial4.write((char*)buf);

              // TODO: RESET LOCAL BUFFER TO EMPTY SO WE KEEP GETTING TELEMETRY MESSAGES BUT DO NOT SEND COMMANDS TWICE
              ledBluetooth->turnOff();
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

      ledLoop->turnOn();
      delay(RADIO_MSG_RATE_MS);
      ledLoop->turnOff();

  }
}
