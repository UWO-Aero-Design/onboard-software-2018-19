// TODO(Carl Baron: Jan 12, 2019): Thought it would be useful to use interface
//                                 separation here but honestly Bluetooth is
//                                 temporary and hopefully obsolete next year
#include "Arduino.h"
#include "Config.h"


// Asynchronous serial flags. Defined by message protocol
// @warning: If the message protocol changes, these values may change
const char start = msg::startByte;
const char end = msg::endByte;
const int  buffersize = 100;

class HC05{
public:
  // Constructors/Destructors
  HC05(Stream *port);
  HC05(Stream *port, uint8_t atPin);
  ~HC05();

  // Initialize bluetooth module
  bool initialize();

  // Baud rate
  bool changeBaud(long baud);
  long checkBaud(void);

  // Write a single byte or an entire message
  void performByteWrite(char msg);
  void performStringWrite(char *msg);
  
  // Read a single byte or an entire message
  char performByteRead(void);
  char* performStringRead(void);

  // Get bluetooth status using AT commands
  int8_t checkRSSI(void);

  // TODO(Carl Baron: Jan 12, 2019): AT Password?
protected:
private:
  Stream *port;
  bool atStatus;
  uint8_t atPin;
};
