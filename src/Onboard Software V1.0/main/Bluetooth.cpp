#include "Arduino.h"
#include "Bluetooth.h"

char * SerialBluetoothReader::read()
{
  // Packet start and end flags
  char SOP = 0x02;
  char EOP = 0x01;

  bool started = false;
  bool ended = false;

  // TODO need to change buffer size based on our needs
  const int dataBufferSize = 80;
  char inData[dataBufferSize];
  byte index = 0;

  // Read all serial data available, as fast as possible
  // TODO try threading this reading functionality
  while(port->available() > 0)
  {
    char inChar = port->read();
    if(inChar == SOP)
    {
      index = 0;
      inData[index] = inChar;
      started = true;
      ended = false;
    }
      
    // TODO: Revisit and fix this
    else if(inChar == EOP)
    {
      // Read message end byte
      inData[index] = inChar;
      index++;

      // Read check sum
      inChar = port->read();
      inData[index] = inChar;
      ended = true;
      break;
    }

    else
    {
      if(index < (dataBufferSize - 1))
      {
        inData[index] = inChar;
        index++;
      }
    }
  }

  // Return full message if received. Else error
  if(started && ended)
  {
    return inData;
  }
  else
  {
    return 0x00;
  }
  
}

// Simple function to write
void SerialBluetoothWriter::write(char * buf)
{
  port->println(buf);
}

HC05Bluetooth::HC05Bluetooth(Stream *port)
{
  // No AT enable pin defined
  ATEnablePin = -1;

  if(bluetoothReader == NULL)
  {
    bluetoothReader = new SerialBluetoothReader(port);
  }

  if(bluetoothWriter == NULL)
  {
    bluetoothWriter = new SerialBluetoothWriter(port);
  }
}

HC05Bluetooth::HC05Bluetooth(Stream *port, int8_t ATPin)
{
  // No AT enable pin defined
  // TODO: Remove 60 with max teensy pin
  if(ATPin > 0 && ATPin < 60)
  {
    ATEnablePin = ATPin;
  }
  else
  {
    Serial.println("AT Pin must be greater than 0 and less than highest pin");
  }

  if(bluetoothReader == NULL)
  {
    bluetoothReader = new SerialBluetoothReader(port);
  }

  if(bluetoothWriter == NULL)
  {
    bluetoothWriter = new SerialBluetoothWriter(port);
  }
}

HC05Bluetooth::~HC05Bluetooth(){
  delete(bluetoothReader);
  delete(bluetoothWriter);
}