#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/*
 * File Purpose
 *    The purpose of this file is to acts as an interface for bluetooth communications
 */

class Bluetooth{
private:
protected:
public:
	Bluetooth(){}
	virtual ~Bluetooth(){}

	virtual char* read() = 0;
	virtual void write(char buf*) = 0;
};

#endif // BLUETOOTH_H
