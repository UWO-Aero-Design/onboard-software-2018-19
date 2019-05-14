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
    SDCardWriter_Teensy(String dirLoc, String filename, String fileHeader);
    ~SDCardWriter_Teensy();
    void init();
    void write(String data);
    void setHeader(String header);
    void setFilename(String filename);
    bool isError();
    String getErrorMessage();

  private:  
    void writeHeader();
    String fileHeader;
    String dirLoc;
    String filename;
    String errorMessage;

};

#endif
