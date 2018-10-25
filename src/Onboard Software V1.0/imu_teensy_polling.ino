#include "IMU_MPU6050.h"

IMU_MPU6050 mpu;

void setup() {
  //xa, ya, za, xg, yg, za
  mpu.init(-3839, -1293, 631, 68, 53, 14);
}


void loop() {
    mpu.update(); 
    Serial.print("ypr\t");
    Serial.print(mpu.getYaw());
    Serial.print("\t");
    Serial.print(mpu.getPitch());
    Serial.print("\t");
    Serial.println(mpu.getRoll());
}
