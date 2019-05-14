#include "HC05TestSystem.h"
#include "SoftwareSerial.h"

HC05BluetoothTestSystem::HC05BluetoothTestSystem(){};
HC05BluetoothTestSystem::~HC05BluetoothTestSystem(){};

void HC05BluetoothTestSystem::initSystem()
{
  SoftwareSerial *myPort = new SoftwareSerial(10,11);
  bluetooth = new HC05(myPort); 
}

// Serial commands from serial monitor for testing different functionality
// W, "Message"
// R
// AT Commands
// TODO: Update factory for bluetooth HC05
void HC05BluetoothTestSystem::updateSystem()
{
  char c = 'T';
  char cc[] = 'Test';

  bluetooth->performByteWrite(c);
  bluetooth->performStringWrite(cc);
  delay(100); 
}
