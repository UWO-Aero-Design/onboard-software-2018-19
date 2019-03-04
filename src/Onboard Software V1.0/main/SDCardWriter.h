#ifndef SDCardWriter_h
#define SDCardWriter_h

/*
 * File Purpose
 *    Interface for the SD Data Logging system
 */

#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class SDCardWriter {
  public: 
    SDCardWriter();
    
    ~SDCardWriter();
    bool isError();
    virtual void init() = 0;
    virtual void write(String data) = 0;
  protected:
    bool error = false;

};

#endif
