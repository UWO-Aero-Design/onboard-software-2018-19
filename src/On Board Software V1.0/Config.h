#ifndef CONFIG_H
#define CONFIG_H

// Enum to outline different operating modes. Plane, Groundstation, Glider
enum systemType{DEFAULT, PLANE, GROUNDSTATION, GLIDER};
const systemType bootType = DEFAULT;

// Motor type definitions
#define _SERVO 					0x100
#define _DC 					0x101
#define _OTHER 					0x102

// Timing variables
#define SENSOR_POLL_RATE_MS 	100
#define SYSTEM_DELAY_MS 		5

// Leftovers from last year
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

uint8_t payload_pins[] = { 12, 13, 15, 14 };
uint16_t payload_open[] = { 1300, 1600, 1925, 1350 };
uint16_t payload_close[] = { 1100, 1700, 1600, 1600 };

uint8_t bay_pins[] = { 8, 9 };
uint16_t bay_open[] = { 950, 2000 };
uint16_t bay_close[] = { 1450, 1500 };



#endif // CONFIG_H
