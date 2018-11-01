#include "IMU.h"
#include "IMU_MPU6050.h"

IMU_MPU6050 imu2;

IMU::IMU() {
  // Constructor
}

float IMU::getYaw() {
    return imu2.getYaw();
}

float IMU::getPitch() {
    return imu2.getPitch();
}

float IMU::getRoll() {
    return imu2.getRoll();
}

void IMU::init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg) {
    imu2.init(xa, ya, za, xg, yg, zg);
}

void IMU::update() {
    imu2.update();
}

void IMU::printYPR() {
    imu2.printYPR();
  }
