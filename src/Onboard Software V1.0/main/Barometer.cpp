#include "Barometer.h"

Barometer::Barometer() : barometerSensorInterface{}, lastUpdate{0} //did not initialize lastUpdate before
{

}

Adafruit_BMP085 Barometer::getBarometerSensorInterface(void)
{
  return barometerSensorInterface;
}

float Barometer::getAltValue(void)
{
  return alt;
}

float Barometer::getTempValue(void)
{
  return temp;
}

float Barometer::getSeaLevelPressureValue(void)
{
  return seaLevelPressure;
}

// void is for the default parameter call
boolean Barometer::init()
{
  return getBarometerSensorInterface().begin();
}

boolean Barometer::init(uint8_t mode)
{
  return getBarometerSensorInterface().begin(mode);
}

uint16_t Barometer::getRawTemperature(void)
{
  return getBarometerSensorInterface().readRawTemperature();
}

uint32_t Barometer::getRawPressure(void)
{
  return getBarometerSensorInterface().readRawPressure();
}

int32_t Barometer::getPressure(void)
{
  return getBarometerSensorInterface().readPressure();
}
// void component id for the default paramter value
int32_t Barometer::getSeaLevelPressure()
{
  return getBarometerSensorInterface().readSealevelPressure();
}

int32_t Barometer::getSeaLevelPressure(float altitude_meters)
{
  return getBarometerSensorInterface().readSealevelPressure(altitude_meters);
}

float Barometer::getTemperature(void)
{
  return getBarometerSensorInterface().readTemperature();
}
// void component is for the default parameter value
float Barometer::getAltitude(void)
{
  return getBarometerSensorInterface().readAltitude();
}

float Barometer::getAltitude(float SeaLevelPressure)
{
  return getBarometerSensorInterface().readAltitude(SeaLevelPressure);
}

void Barometer::zero(void)
{
  zero(getSeaLevelPressure(0));
}

void Barometer::zero(float seaLevelPressure)
{
  this->alt = 0;
  this->seaLevelPressure = seaLevelPressure; //change function parameter name to not use this?
}
  
void Barometer::update()
{
  long curlTime = millis();

  if (curlTime - lastUpdate < 1000)
    return;

  alt = 0.2*getAltitude(seaLevelPressure) + 0.8*alt;
  temp = getTemperature();
  lastUpdate = curlTime;  
}
