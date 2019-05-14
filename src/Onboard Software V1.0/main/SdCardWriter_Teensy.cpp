#include "SDCardWriter_Teensy.h"
#include <SD.h>

const int chipSelect = BUILTIN_SDCARD; // SD Card location - Teensy is built in

SDCardWriter_Teensy::SDCardWriter_Teensy() {
  dirLoc = "logs/"; // location of the directory for logs
  filename = "log1"; // name of the file
  fileHeader = ""; // what to include as a header
}

SDCardWriter_Teensy::SDCardWriter_Teensy(String dirLoc, String filename, String fileHeader) {
  this->dirLoc = dirLoc; // location of the directory for logs
  this->filename = filename; // name of the file
  this-> fileHeader = fileHeader; // what to include as a header
}

SDCardWriter_Teensy::~SDCardWriter_Teensy() { }

void SDCardWriter_Teensy::init() {
  if(!Serial) Serial.begin(9600); // open serial for debugging

  //Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized
  if (!SD.begin(chipSelect)) {
    errorMessage = "Card failed, or not present";
    error = true;
  }
  else {
  //Serial.println("Card initialized."); // success
  
  if(SD.exists("logs")) SD.mkdir("logs"); // make the new directory

  writeHeader(); // write the header to the file
  }
}

// writes the parameter to the SD card
void SDCardWriter_Teensy::write(String data) {
  if(error) return;
  String s = dirLoc + filename;
  File file = SD.open(s.c_str(), FILE_WRITE); // open file

  if (file) { // print to file
    file.print("[");
    file.print(millis()); // timestamp
    file.print("]\t");
    file.println(data);
    file.close();
  }
  else { // couldn't open file
    Serial.println("Error opening file.");
    errorMessage = "Error opening file.";
    error = true;
  }
}

// very similar to writeSD() but  writes the header specifically
void SDCardWriter_Teensy::writeHeader() { 
  String s = dirLoc + filename;
  File file = SD.open(s.c_str(), FILE_WRITE); // open file

  if (file) {  // print to file
    file.println("\n\n\n-------------------------------------"); 
    file.println(fileHeader);
    file.println("-------------------------------------\n\n");
    file.close();
    //Serial.println("Header written to SD.");
  }
  else {  // couldn't open file
    errorMessage = "Error opening file.";
    error = true;
    //Serial.println("Error opening file.");
  }
}

// sets the name of the file
void SDCardWriter_Teensy::setFilename(String filename) { 
  this->filename = filename;
}

// sets the text that is the header
void SDCardWriter_Teensy::setHeader(String header) {
  fileHeader = header;
}

// returns if there has been an error
bool SDCardWriter_Teensy::isError() {
  return error;
}

// returns what the error was
String SDCardWriter_Teensy::getErrorMessage() {
  return errorMessage;
}
