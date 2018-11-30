#include "Barometer.h"

Barometer::Barometer() : barometerSensorInterface{}, lastUpdate{0} //did not initialize lastUpdate before
{

}

Adafruit_BMP085 Barometer::barometerGetBarometerSensorInterface(void)
{
  return barometerSensorInterface;
}

float Barometer::barometerGetAltValue(void)
{
  return alt;
}

float Barometer::barometerGetTempValue(void)
{
  return temp;
}

float Barometer::barometerGetSeaLevelPressureValue(void)
{
  return seaLevelPressure;
}

// void is for the default parameter call
boolean Barometer::barometerBegin()
{
  return barometerGetBarometerSensorInterface().begin();
}

boolean Barometer::barometerBegin(uint8_t mode)
{
  return barometerGetBarometerSensorInterface().begin(mode);
}

uint16_t Barometer::barometerReadRawTemperature(void)
{
  return barometerGetBarometerSensorInterface().readRawTemperature();
}

uint32_t Barometer::barometerReadRawPressure(void)
{
  return barometerGetBarometerSensorInterface().readRawPressure();
}

int32_t Barometer::barometerReadPressure(void)
{
  return barometerGetBarometerSensorInterface().readPressure();
}
// void component id for the default paramter value
int32_t Barometer::barometerReadSeaLevelPressure()
{
  return barometerGetBarometerSensorInterface().readSealevelPressure();
}

int32_t Barometer::barometerReadSeaLevelPressure(float altitude_meters)
{
  return barometerGetBarometerSensorInterface().readSealevelPressure(altitude_meters);
}

float Barometer::barometerReadTemperature(void)
{
  return barometerGetBarometerSensorInterface().readTemperature();
}
// void component is for the default parameter value
float Barometer::barometerReadAltitude(void)
{
  return barometerGetBarometerSensorInterface().readAltitude();
}

float Barometer::barometerReadAltitude(float SeaLevelPressure)
{
  return barometerGetBarometerSensorInterface().readAltitude(SeaLevelPressure);
}

void Barometer::barometerZero(void)
{
  barometerZero(barometerReadSeaLevelPressure(0));
}

void Barometer::barometerZero(float seaLevelPressure)
{
  this->alt = 0;
  this->seaLevelPressure = seaLevelPressure; //change function parameter name to not use this?
}
  
void Barometer::barometerUpdate()
{
  long curlTime = millis();

  if (curlTime - lastUpdate < 1000)
    return;

  alt = 0.2*barometerReadAltitude(seaLevelPressure) + 0.8*alt;
  temp = barometerReadTemperature();
  lastUpdate = curlTime;  
}
