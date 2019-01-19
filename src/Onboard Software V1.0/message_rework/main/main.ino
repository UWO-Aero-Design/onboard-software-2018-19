#include "Message.h"

void setup(){
  Serial.begin(9600);

  Message msgr;
  msg::aircraft_message_t air = {0,16,0,0,0,0,0,0,0,0,0,0,0,0};
  msg::message_t msg = msgr.buildMessage(config::thisSystem, air);

  int32_t x = 0;
  memcpy(&x, msg.packet.buf+4,sizeof(4));
  Serial.println(x);
}

void loop(){

}

// Used for debugging by allowing us to print a hex string based on an input char* buffer
void printHex(char *buf, int len) 
{
  for (int i = 0; i < len; i++) {
  Serial.println(buf[i] & 0xFF, HEX);
    if (i == (len) - 1) { Serial.println(""); }
  }
}