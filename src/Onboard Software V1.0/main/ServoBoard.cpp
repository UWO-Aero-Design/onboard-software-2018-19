#include "ServoBoard.h"

Adafruit_PWMServoDriver driver;

ServoBoard::ServoBoard() {
  driver = Adafruit_PWMServoDriver();
}


ServoBoard::~ServoBoard() { }

void ServoBoard::init() {
  driver.begin();
  driver.setPWMFreq(50); // set clock frequency
}

// init with number of channels - ie. 0 to 8
void ServoBoard::init(int numChannels) {
  this->numChannels = numChannels;
  this->maxChannel = numChannels - 1;
  init();
}

// init with a min and max channel number - ie. 8 to 15
void ServoBoard::init(int minChannel, int maxChannel) {
  this->numChannels = maxChannel - minChannel + 1;
  this->maxChannel = maxChannel;
  this->minChannel = minChannel;
  init();
}

// checks if input is valid and runs the coresponding servo
// gpIO:
//        full on  - driver.setPWM(channel, 4096,   0 );
//        full off - driver.setPWM(channel,   0 , 4096);
void ServoBoard::runServo(int channel, int pulse) {
  if(channel > maxChannel || channel < minChannel) {
    error = true;
    errorMsg = "Invalid Channel";
    return;
  }
  if(pulse < 0 || pulse > 4096) {
    error = true;
    errorMsg = "Invalid Pulse Length";
  }
  driver.setPWM(channel, 0, pulse);
}

bool ServoBoard::isError() {
  return error;
}

String ServoBoard::getErrorMsg() {
  error = false;
  return errorMsg;
}
