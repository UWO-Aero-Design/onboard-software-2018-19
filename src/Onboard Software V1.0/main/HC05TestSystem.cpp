#include "HC05TestSystem.h"

HC05BluetoothTestSystem::HC05BluetoothTestSystem();
HC05BluetoothTestSystem::~HC05BluetoothTestSystem();

void HC05BluetoothTestSystem::initSystem()
{
  bluetooth = new HC05Bluetooth(&Serial); 
}

// Serial commands from serial monitor for testing different functionality
// W, "Message"
// R
// AT Commands
// TODO: Update factory for bluetooth HC05
void HC05BluetoothTestSystem::updateSystem()
{
 char* msg = bluetooth->performRead();
 bluetooth->performWrite("Hello"); 
}