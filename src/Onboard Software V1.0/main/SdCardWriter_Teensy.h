#ifndef SDCardWriterTeensy_h
#define SDCardWriterTeensy_h

#include "SDCardWriter.h"

#if(ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class SDCardWriter_Teensy : public SDCardWriter{
  public: 
    SDCardWriter_Teensy();
    ~SDCardWriter_Teensy();
    void initSD();
    void writeSD(String data);
    void setHeader(String header);
    void setFilename(String filename);
    bool isError();

  private:  
    void writeHeader();
    String fileHeader;
    String dir_loc;
    String filename;

};

#endif
