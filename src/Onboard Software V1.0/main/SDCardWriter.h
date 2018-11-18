#ifndef SDCardWriter_h
#define SDCardWriter_h

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
    virtual void initSD() = 0;
    virtual void writeSD(String data) = 0;
  protected:
    bool error = false;

};

#endif
