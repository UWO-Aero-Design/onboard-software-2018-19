#ifndef SERVO_BOARD_H
#define SERVO_BOARD_H

#include <Arduino.h>
#include <Wire.h>

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

#define SB_THROT  0
#define SB_NOSE   1
#define SB_WING_L 2
#define SB_WING_R 3
#define SB_ELEV_L 4
#define SB_ELEV_R 5
#define SB_RUDD   6
#define SB_BAY_L  7
#define SB_BAY_R  8
#define SB_PAY_FL 9
#define SB_PAY_FR 10
#define SB_PAY_BL 11
#define SB_PAY_BR 12

class ServoBoard {
 public:
  ServoBoard(uint8_t addr = 0x40);
  void begin(void);
  void reset(void);
  void setPWMFreq(float freq);
  void setPWM(uint8_t num, uint16_t millis);

 private:
  uint8_t _i2caddr;
  
  TwoWire *_i2c;

  float _ticksPerMicrosecond;

  uint8_t read8(uint8_t addr);
  void write8(uint8_t addr, uint8_t d);
};

#endif // SERVO_BOARD_H
