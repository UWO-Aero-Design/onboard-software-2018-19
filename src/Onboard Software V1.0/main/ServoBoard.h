#ifndef ServoBoard_h
#define ServoBoard_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>



#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ServoBoard {
  public: 
    ServoBoard();
    ~ServoBoard();
    void init();
    void init(int numChannels);
    void init(int minChannel, int maxChannel);
    void runServo(int channel, int pulse);
    bool isError();
    String getErrorMsg();

  private:
    int numChannels = 16, minChannel = 0, maxChannel = 15; 
    bool error = false;
    String errorMsg = "";

};


#endif
