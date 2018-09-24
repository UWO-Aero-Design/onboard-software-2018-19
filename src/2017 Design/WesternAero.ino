#include <stdint.h>
#include <Wire.h>
#include "Barometer.h"
#include "GPS.h"
#include "IMU.h"
#include "ServoBoard.h"

#define TELEMETRY_RATE  1000
#define MSG_START     0x02
#define MSG_TELEM     0x00
#define MSG_LOAD      0x00
#define MSG_UNLOAD    0x01
#define MSG_ZERO_BARO 0x02
#define MSG_ZERO_GPS  0x03
#define MSG_BAY_OPEN  0x04
#define MSG_BAY_CLOSE 0x05
#define DROP          0x06

uint8_t msgLengths[] = { 1, 1, 0, 0, 0, 0, 0 };

long t;
Barometer baro;
IMU imu;
GPS gps;
ServoBoard sb;

bool doorsClose = true;
bool start = false;
int id = -1;

long lastMsg = 0;

byte buf[256];
uint8_t bufPos = 0;
uint8_t checksum = 0;

float dropHeight = -1;

int msgId = -1;

float distToDrop, bearingToDrop;

uint8_t payload_pins[] = { 12, 13, 15, 14 };
uint16_t payload_open[] = { 1300, 1600, 1925, 1350 };
uint16_t payload_close[] = { 1100, 1700, 1600, 1600 };

uint8_t bay_pins[] = { 8, 9 };
uint16_t bay_open[] = { 950, 2000 };
uint16_t bay_close[] = { 1450, 1500 };

void dropAlgorithm(float x, float y, float z, float vx, float vy, float vz, float targetX, float targetY, float targetZ) {
	float ax = 0, ay = 0, az = -9.81, t = 0;
	const float dt = 0.01;
	
	while (z > targetZ) {
		vx += ax * dt;
		vy += ay * dt;
		vz += az * dt;

		x += vx * dt;
		y += vy * dt;
		z += vz * dt;

		t += dt;
	}

	float diffX = targetX - x;
	float diffY = targetY - y;

	distToDrop = sqrt(diffX * diffX + diffY * diffY);
	bearingToDrop = 180 * atan2(diffX, diffY) / PI;
}

void openDoors() {
  doorsClose = false;
  sb.setPWM(bay_pins[0], bay_open[0]);
  sb.setPWM(bay_pins[1], bay_open[1]);
}

void closeDoors() {
  doorsClose = true;
  sb.setPWM(bay_pins[0], bay_close[0]);
  sb.setPWM(bay_pins[1], bay_close[1]);
}

void drop() {
  if (doorsClose) return;

  dropHeight = baro.alt;
  for (int i = 0; i < 4; i++) {
    sb.setPWM(payload_pins[i], payload_open[i]);
  }
}

void sendFloat(float f) {
  uint8_t *bytes = (uint8_t*) &f;
  for (int i = 3; i >= 0; i--) {
    Serial5.write(bytes[i]);
  }
}

void parseMsg(uint8_t *buf) {
	switch(msgId) {
	case MSG_LOAD:
    Serial.print("load ");
    Serial.println(buf[0]);
    dropHeight = -1;
		sb.setPWM(payload_pins[buf[0]], payload_close[buf[0]]);
	break;
	
	case MSG_UNLOAD:
    Serial.print("unload ");
    Serial.println(buf[0]);
		sb.setPWM(payload_pins[buf[0]], payload_open[buf[0]]);
	break;
	
	case MSG_ZERO_BARO:
    Serial.println("zero baro");
		baro.zero();
	break;
	
	case MSG_ZERO_GPS:
    Serial.println("zero gps");
		gps.zero();
	break;
	
	case MSG_BAY_OPEN:
    Serial.println("bay open");
		openDoors();
	break;
	
	case MSG_BAY_CLOSE:
    Serial.println("bay close");
		closeDoors();
	break;
	
	case DROP:
    Serial.println("drop");
    drop();
	break;
	}
}

void setup() {
	Serial5.begin(57600);
	sb.begin();
	baro.begin();
	imu.init();
	gps.init();

	baro.zero();
	gps.zero(27.97816585, -82.02474327);

	//attachInterrupt(digitalPinToInterrupt(pins[0]), pwm0, CHANGE);

	delay(10);
}

void loop() {
	baro.update();
	imu.update();
	gps.update();

  //dropAlgorithm(gps.x, gps.y, baro.alt, gps.speed*sin(gps.course), gps.speed*cos(gps.course), 0, 0, 0, 0);

  long curTime = millis();
  if (curTime - lastMsg > 750) {
    Serial5.write(MSG_START);
    Serial5.write(MSG_TELEM);
    sendFloat(gps.lat);
    sendFloat(gps.lon);
    sendFloat(baro.alt);
    sendFloat(imu.roll);
    sendFloat(imu.pitch);
    sendFloat(imu.yaw);
    sendFloat(gps.speed);
    sendFloat(gps.course);
    sendFloat(dropHeight);
    
    lastMsg = curTime;
  }

  while (Serial5.available()) {
    Serial.print(Serial5.peek(), HEX);
  	if (!start) {
      start = Serial5.read() == MSG_START;
  	} else if (msgId == -1) {
      msgId = Serial5.read();
      bufPos = 0;
      checksum = MSG_START ^ msgId;
  	} else if (msgLengths[msgId] == bufPos) {
      if (checksum == Serial5.read()) {
        parseMsg(buf);
  	  }

      start = false;
      msgId = -1;
  	} else {
      uint8_t c = Serial5.read();
      checksum ^= c;
      buf[bufPos++] = c;
  	}
  }

	delay(5);
}

