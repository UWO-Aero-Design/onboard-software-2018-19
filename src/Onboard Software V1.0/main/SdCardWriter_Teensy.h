#ifndef SDCardWriterTeensy_h
#define SDCardWriterTeensy_h

/*
 * File Purpose
 *    Implements the SDCardWriter class to work with Teensy's SD system
 */

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

    // error handling
    bool isError();
    String getErrorMessage();

  private:  
    void writeHeader();
    String fileHeader; // header for the file
    String dirLoc; // location of the directory
    String filename; // name of the file
    String errorMessage; // any errors

};

#endif
