//#ifndef BAROMETER_H
//#define BAROMETER_H
//
//#include <Adafruit_BMP085.h>
//
//class Barometer 
//{
// public:
//  Barometer();
//  boolean init(uint8_t mode);
//  boolean init();
//  float getTemperature(void);
//  int32_t getPressure(void);
//  int32_t getSeaLevelPressure(void);
//  int32_t getSeaLevelPressure(float altitude_meters);
//  float getAltitude(float seaLevelPressure);
//  float getAltitude(void);
//  uint16_t getRawTemperature(void);
//  uint32_t getRawPressure(void);
//  void zero(void);
//  void zero(float seaLevelPressure);
//  void update(void);
//  float getAltValue(void);
//  float getTempValue(void);
//  float getSeaLevelPressureValue(void);
//  Adafruit_BMP085 getBarometerSensorInterface(void);
//
// private:
//  float alt, temp, seaLevelPressure = 101325;
//  Adafruit_BMP085 barometerSensorInterface;
//  long lastUpdate;
//};
//#endif
