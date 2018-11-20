#include "IMU.h"

IMU::IMU() { }

float IMU::getYaw() {
  return yaw;
}

float IMU::getRoll() {
  return roll;
}

float IMU::getPitch() {
  return pitch;
}

IMU::~IMU() { }
