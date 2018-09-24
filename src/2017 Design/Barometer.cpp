#include "Barometer.h"

Barometer::Barometer() {
}


boolean Barometer::begin(uint8_t mode) {
  if (mode > BMP085_ULTRAHIGHRES) 
    mode = BMP085_ULTRAHIGHRES;
  oversampling = mode;

  Wire.begin();

  if (read8(0xD0) != 0x55) return false;

  /* read calibration data */
  ac1 = read16(BMP085_CAL_AC1);
  ac2 = read16(BMP085_CAL_AC2);
  ac3 = read16(BMP085_CAL_AC3);
  ac4 = read16(BMP085_CAL_AC4);
  ac5 = read16(BMP085_CAL_AC5);
  ac6 = read16(BMP085_CAL_AC6);

  b1 = read16(BMP085_CAL_B1);
  b2 = read16(BMP085_CAL_B2);

  mb = read16(BMP085_CAL_MB);
  mc = read16(BMP085_CAL_MC);
  md = read16(BMP085_CAL_MD);

  return true;
}

int32_t Barometer::computeB5(int32_t UT) {
  int32_t X1 = (UT - (int32_t)ac6) * ((int32_t)ac5) >> 15;
  int32_t X2 = ((int32_t)mc << 11) / (X1+(int32_t)md);
  return X1 + X2;
}

uint16_t Barometer::readRawTemperature(void) {
  write8(BMP085_CONTROL, BMP085_READTEMPCMD);
  return read16(BMP085_TEMPDATA);
}

uint32_t Barometer::readRawPressure(void) {
  uint32_t raw;

  write8(BMP085_CONTROL, BMP085_READPRESSURECMD + (oversampling << 6));

  if (oversampling == BMP085_ULTRALOWPOWER) 
    delay(5);
  else if (oversampling == BMP085_STANDARD) 
    delay(8);
  else if (oversampling == BMP085_HIGHRES) 
    delay(14);
  else 
    delay(26);

  raw = read16(BMP085_PRESSUREDATA);

  raw <<= 8;
  raw |= read8(BMP085_PRESSUREDATA+2);
  raw >>= (8 - oversampling);

  return raw;
}

int32_t Barometer::readPressure(void) {
  int32_t UT, UP, B3, B5, B6, X1, X2, X3, p;
  uint32_t B4, B7;

  UT = readRawTemperature();
  delay(5);
  UP = readRawPressure();

  B5 = computeB5(UT);

  // do pressure calcs
  B6 = B5 - 4000;
  X1 = ((int32_t)b2 * ( (B6 * B6)>>12 )) >> 11;
  X2 = ((int32_t)ac2 * B6) >> 11;
  X3 = X1 + X2;
  B3 = ((((int32_t)ac1*4 + X3) << oversampling) + 2) / 4;

  X1 = ((int32_t)ac3 * B6) >> 13;
  X2 = ((int32_t)b1 * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  B4 = ((uint32_t)ac4 * (uint32_t)(X3 + 32768)) >> 15;
  B7 = ((uint32_t)UP - B3) * (uint32_t)( 50000UL >> oversampling );

  if (B7 < 0x80000000) {
    p = (B7 * 2) / B4;
  } else {
    p = (B7 / B4) * 2;
  }
  X1 = (p >> 8) * (p >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * p) >> 16;

  p = p + ((X1 + X2 + (int32_t)3791)>>4);
  return p;
}

int32_t Barometer::readSealevelPressure(float altitude_meters) {
  float pressure = readPressure();
  return (int32_t)(pressure / pow(1.0-altitude_meters/44330, 5.255));
}

float Barometer::readTemperature(void) {
  int32_t UT, B5;     // following ds convention
  float temp;

  UT = readRawTemperature();
  B5 = computeB5(UT);
  temp = (B5+8) >> 4;
  temp /= 10;
  
  return temp;
}

float Barometer::readAltitude(float sealevelPressure) {
  float altitude;

  float pressure = readPressure();

  altitude = 44330 * (1.0 - pow(pressure /sealevelPressure,0.1903));

  return altitude;
}

void Barometer::zero() {
  zero(readSealevelPressure(0));
}

void Barometer::zero(float seaLevelPressure) {
  this->alt = 0;
  this->seaLevelPressure = seaLevelPressure;
}

void Barometer::update() {
  long curTime = millis();

  if (curTime - lastUpdate < 1000)
    return;

  alt = 0.2*readAltitude(seaLevelPressure) + 0.8*alt;
  temp = readTemperature();
  lastUpdate = curTime;
}


/*********************************************************************/

uint8_t Barometer::read8(uint8_t a) {
  uint8_t ret;

  Wire.beginTransmission(BMP085_I2CADDR);
  Wire.write(a);
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device 
  Wire.requestFrom(BMP085_I2CADDR, 1);// send data n-bytes read
  ret = Wire.read();
  Wire.endTransmission(); // end transmission

  return ret;
}

uint16_t Barometer::read16(uint8_t a) {
  uint16_t ret;

  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device 
  Wire.write(a);
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device 
  Wire.requestFrom(BMP085_I2CADDR, 2);// send data n-bytes read
  ret = Wire.read();
  ret <<= 8;
  ret |= Wire.read();
  Wire.endTransmission(); // end transmission

  return ret;
}

void Barometer::write8(uint8_t a, uint8_t d) {
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device
  Wire.write(a); // sends register address to read from
  Wire.write(d);  // write data
  Wire.endTransmission(); // end transmission
}

