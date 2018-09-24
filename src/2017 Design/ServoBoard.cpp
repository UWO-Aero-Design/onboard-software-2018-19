#include "ServoBoard.h"
#include <Wire.h>

ServoBoard::ServoBoard(uint8_t addr) {
	_i2caddr = addr;
	_i2c = &Wire;
}

void ServoBoard::begin(void) {
	_i2c->begin();
	reset();
	// set a default frequency
	setPWMFreq(50);
}

void ServoBoard::reset(void) {
	write8(PCA9685_MODE1, 0x80);
	delay(10);
}

void ServoBoard::setPWMFreq(float freq) {
	_ticksPerMicrosecond = 4096 * freq / 1000000;

	freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;

	uint8_t prescale = floor(prescaleval + 0.5);

	uint8_t oldmode = read8(PCA9685_MODE1);
	uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
	write8(PCA9685_MODE1, newmode); // go to sleep
	write8(PCA9685_PRESCALE, prescale); // set the prescaler
	write8(PCA9685_MODE1, oldmode);
	delay(5);
	write8(PCA9685_MODE1, oldmode | 0xa0);  //  This sets the MODE1 register to turn on auto increment.
	delay(10);
}

void ServoBoard::setPWM(uint8_t num, uint16_t micros) {
	micros *= _ticksPerMicrosecond;

	_i2c->beginTransmission(_i2caddr);
	_i2c->write(LED0_ON_L+4*num);
	_i2c->write(0);
	_i2c->write(0);
	_i2c->write(micros);
	_i2c->write(micros>>8);
	_i2c->endTransmission();
}

/*******************************************************************************************/

uint8_t ServoBoard::read8(uint8_t addr) {
	_i2c->beginTransmission(_i2caddr);
	_i2c->write(addr);
	_i2c->endTransmission();

	_i2c->requestFrom((uint8_t)_i2caddr, (uint8_t)1);
	return _i2c->read();
}

void ServoBoard::write8(uint8_t addr, uint8_t d) {
	_i2c->beginTransmission(_i2caddr);
	_i2c->write(addr);
	_i2c->write(d);
	_i2c->endTransmission();
}
