#ifndef BLUETOOTH_H
#define BLUETOOTH_H
/*
 *  File contains basic bluetooth abstract class
 *  Also contains interfaces and interface implementations
 */
#include "Arduino.h"

// Interface to encapsulate reading a bluetooth message in
class BluetoothReader{
public:
  virtual char* read() = 0;
};

// Implementation of BluetoothReader for a SMP Bluetooth Module
class SerialBluetoothReader : public BluetoothReader{
private:
  Stream *port;
public:
  SerialBluetoothReader(Stream *port){this->port = port;}
  char* read();
};

// Interface to encapsulate writing a bluetooth message in
class BluetoothWriter{
public:
  virtual void write(char *buf) = 0;
};

// Implementation of BluetoothReader for a SMP Bluetooth Module
class SerialBluetoothWriter : public BluetoothWriter{
private:
  Stream *port;
public:
  SerialBluetoothWriter(Stream *port){this->port = port;}
  void write(char *buf);
};

// Planned for AT mode. Used during test
// Definitely not required right now
class BluetoothManager{
public:
  virtual char* getVersion() = 0;
  virtual char* setSystemDefault() = 0;
  virtual char* getModuleAddress() = 0;
  virtual char* setModuleName(char* name) = 0;
  virtual char* getModuleName() = 0;
  virtual char* getRSSI() = 0;
  virtual char* setPassword() = 0;
  virtual char* getPassword() = 0;
};

class HC05BluetoothManager : public BluetoothManager{
public:
  char* getVersion();
  char* setSystemDefault();
  char* getModuleAddress();
  char* setModuleName(char* name);
  char* getModuleName();
  char* getRSSI();
  char* setPassword(char* pswd);
  char* getPassword();
};

// Bluetooth class where interface implementation is coded to the base class
// Has bluetooth reader and bluetooth writer objects
class Bluetooth{
private:
protected:
  BluetoothReader *bluetoothReader = NULL;
  BluetoothWriter *bluetoothWriter = NULL;
  // BluetoothManager *bluetoothManager;
public:
	Bluetooth(){}
	virtual ~Bluetooth(){}

  char* performRead(){ bluetoothReader->read(); }
  void  performWrite(char *buf){ bluetoothWriter->write(buf); }
  // void  getConnectionStatus(){ bluetoothManager->status(); }

};

// Specifically for HC05 or any SMP module really
// TODO: AT Commands
class HC05Bluetooth : public Bluetooth{
private:
  bool    ATStatus    = false; 
  int8_t  ATEnablePin = 0;
protected:
public:
  // Define which interface implementation to use
  HC05Bluetooth(Stream *port);
  HC05Bluetooth(Stream *port, int8_t ATPin);
  ~HC05Bluetooth();

  // TODO: Implementation for AT Commands
};


#endif // BLUETOOTH_H
