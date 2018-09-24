#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include <Wire.h>

#define ACC_SENS     0.002F
#define GYR_SENS     PI * 0.00875F / 180
#define MAG_SENS_XY  (1.0F/1100)
#define MAG_SENS_Z   (1.0F/980)

#define ACC_ADDR     0x19 // Accelerometer data
#define ACC_DATA     0xA8 // Register at data start
#define GYR_ADDR     0x6B
#define GYR_DATA     0xA8
#define MAG_ADDR     0x1E
#define MAG_DATA     0x03
#define TMP_DATA     0x31

#define betaDef      0.1f    // 2 * proportional gain

class IMU {
public:
	void init();
	void readAcc();
	void readGyr();
	void readMag();
	void readBar();
	void update();

	float acc[3], gyr[3], mag[3], temp;
	float roll, pitch, yaw;

private:
	void writeTo(uint8_t address, uint8_t reg, uint8_t val);
	void readFrom(uint8_t address, uint8_t reg, uint8_t numBytes);
	float invSqrt(float x);
	void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
	void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);

	float beta = betaDef;
	float q0 = 1.0, q1 = 0.0, q2 = 0.0, q3 = 0.0;
	long lastMicros;
	float period;

	float gyr_offset[3] = {-0.02845, -0.10664, 0.01414};
};



#endif // IMU_H
