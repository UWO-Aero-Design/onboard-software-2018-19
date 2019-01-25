#ifndef BAROMETER_H
#define BAROMETER_H

#include <Adafruit_BMP085.h>

class Barometer 
{
 public:
  Barometer();
  boolean barometerBegin(uint8_t mode);
  boolean barometerBegin();
  float barometerReadTemperature(void);
  int32_t barometerReadPressure(void);
  int32_t barometerReadSeaLevelPressure(void);
  int32_t barometerReadSeaLevelPressure(float altitude_meters);
  float barometerReadAltitude(float seaLevelPressure);
    float barometerReadAltitude(void);
  uint16_t barometerReadRawTemperature(void);
  uint32_t barometerReadRawPressure(void);

  void barometerZero(void);
  void barometerZero(float seaLevelPressure);
  void barometerUpdate(void);


  float barometerGetAltValue(void);
  float barometerGetTempValue(void);
  float barometerGetSeaLevelPressureValue(void);
  Adafruit_BMP085 barometerGetBarometerSensorInterface(void);

 private:
  float alt, temp, seaLevelPressure = 101325;
  Adafruit_BMP085 barometerSensorInterface;
  long lastUpdate;
};
#endif
