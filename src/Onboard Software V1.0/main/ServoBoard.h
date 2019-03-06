#ifndef ServoBoard_h
#define ServoBoard_h

/*
 * File Purpose
 *    Interface between Adafruit's PWMServoDriver Library and the System
 */

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

    // different inits for different channel structures
    void init();
    void init(int numChannels);
    void init(int minChannel, int maxChannel);

    // main servo running method
    void runServo(int channel, int pulse);

    void glider_actuate(int channel);
    void glider_stop(int channel);

    // error handling
    bool isError();
    String getErrorMsg();

  private:
    int numChannels = 16, minChannel = 0, maxChannel = 15; // default settings
    bool error = false;
    String errorMsg = "";

};


#endif
