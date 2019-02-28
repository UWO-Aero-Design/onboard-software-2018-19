#include "HC05.h"


HC05::HC05(Stream *port)
{
  this->port = port;
  this->atPin = 255;
  this->atStatus = false;
}

HC05::HC05(Stream *port, uint8_t atPin)
{
  this->port = port;
  this->atPin = atPin;
  this->atStatus = true;
}

HC05::~HC05(){
  this->port = NULL;
  this->atPin = 255;
  this->atStatus = false;
}

// Initialize bluetooth module
bool HC05::initialize(){};

// Baud rate
bool HC05::changeBaud(long baud){};
long HC05::checkBaud(void){};

void HC05::performByteWrite(char msg){
  port->println(msg);
}

void HC05::performStringWrite(char *msg)
{
  port->println(msg);
}
  
// Read a single byte
char HC05::performByteRead(void)
{
  if(port->available())
  {
    return port->read();
  }
  else
  {
    return 0x00;
  }
}

// TODO(Carl Baron: Jan 13th, 2019): Implement
// Read an entire message
char* HC05::performStringRead(void)
{
  char buffer[100];
  bool started = false;
  bool ended = false;
  uint8_t index = 0;

  while(port->available() > 0)
  {
    char in = port->read();
    // If the input byte is the start byte, reset the buffer
    if(in == start)
    {
      index = 0;
      buffer[index] = in;
      started = true;
      ended = false;
    }
    // If the input byte is the end byte, end the bufer
    // TODO(Carl Baron: Jan 12th, 2019): Move crc before end of packet
    else if(in == ended)
    {
      buffer[index] = in;
      ended = true;
      break;
    }
    // If the byte is between start and end
    else if(started == true)
    {
      if(index < (buffersize - 1))
      {
        buffer[index] = in;
        index += 1;
      }
    }
  }

  // If we read the entire serial port and got both a start and end byte
  // Return the valid data. Else return an 0
  if(started && ended)
  {
    return buffer;
  }
  else
  {
    return 0x00;
  }
}

// TODO(Carl Baron: Jan 13th, 2019): Implement
// Get bluetooth status using AT commands
int8_t HC05::checkRSSI(void){};
