#include "Message.h"
#include "HC05.h"
#include "SoftwareSerial.h"

HC05 *hc05;
SoftwareSerial *myPort = new SoftwareSerial(10,11);

msg::message_t msg_;

void setup(){
  Serial.begin(9600);
  myPort->begin(9600);

  Message msgr;
  msg::aircraft_message_t air = {0,16,0,0,0,0,0,0,0,0,0,0,0,0};
  msg_ = msgr.buildMessage(config::thisSystem, air);
  hc05 = new HC05(myPort);

}

void loop(){
  char *test = "test";

  int32_t lon = 0;
  memcpy(&lon, msg_.packet.buf+4, 4);
  Serial.println(lon);
  
  hc05->performByteWrite(lon);
  delay(1000);
}
