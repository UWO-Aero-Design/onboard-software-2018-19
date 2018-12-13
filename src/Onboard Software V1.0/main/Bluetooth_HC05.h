#ifndef BLUETOOTH__HC05_H
#define BLUETOOTH__HC05_H


/*
 * File Purpose
 *    The purpose of this file is to implement the bluetooth interface
 *    With the specific bluetooth chip being the HC-05
 */

#include "Bluetooth.h"

class BluetoothHC05 : public Bluetooth{
private:
protected:
public:
	BluetoothHC05(){}
	virtual ~BluetoothHC05(){}

	char* read();
	void write(char buf*);
};

#endif // BLUETOOTH__HC05_H
