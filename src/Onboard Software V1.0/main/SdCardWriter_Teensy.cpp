#include "SDCardWriter_Teensy.h"
#include <SD.h>

const int chipSelect = BUILTIN_SDCARD; // SD Card location

SDCardWriter_Teensy::SDCardWriter_Teensy() {
  dir_loc = "logs/";
  filename = "log1";
  fileHeader = "";
}

SDCardWriter_Teensy::~SDCardWriter_Teensy() { }

void SDCardWriter_Teensy::initSD() {
  if(!Serial) Serial.begin(9600);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    error = true;
  }
  else {
  Serial.println("Card initialized."); // success

  SD.mkdir("logs"); // make the new directory

  writeHeader();
  }
}

void SDCardWriter_Teensy::writeSD(String data) {
  if(error) return;
  File file = SD.open("logs/datalog.txt", FILE_WRITE); // open file

  if (file) { // print to file
    file.print("[");
    file.print(millis());
    file.print("]\t");
    file.println(data);
    file.close();
   // Serial.print("Writing to SD:\t");
   // Serial.println(data);
  }
  else { // couldn't open file
    Serial.println("Error opening file.");
    error = true;
  }
}

void SDCardWriter_Teensy::writeHeader() { 
  String s = dir_loc + filename;
  File file = SD.open(s.c_str(), FILE_WRITE); // open file

  if (file) {  // print to file
    file.println("\n\n\n-------------------------------------"); 
    file.println(fileHeader);
    file.println("-------------------------------------\n\n");
    file.close();
    Serial.println("Header written to SD.");
  }
  else {  // couldn't open file
    Serial.println("Error opening file.");
  }
}

void SDCardWriter_Teensy::setFilename(String filename) { 
  this->filename = filename;
}

void SDCardWriter_Teensy::setHeader(String header) {
  fileHeader = header;
}

bool SDCardWriter_Teensy::isError() {
  return error;
}
