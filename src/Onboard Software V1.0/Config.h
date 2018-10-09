#ifndef CONFIG_H
#define CONFIG_H

// Enum to outline different operating modes. Plane, Groundstation, Glider
enum SystemType{SYS_DEFAULT, SYS_PLANE, SYS_GROUNDSTATION, SYS_GLIDER};
const systemType bootType = SYS_DEFAULT;

// Enum to outline different command types
enum CommandType{CMD_LOAD, CMD_UNLOAD, CMD_ZERO, CMD_BAY_OPEN, CMD_BAY_CLOSE, CMD_DROP};

// Enum to outline different radio configurations
enum RadioType{RADIO_SLAVE, RADIO_MASTER, RADIO_TEST_SLAVE, RADIO_TEST_MASTER};

// Enum to outline different bluetooth configurations
enum BluetoothType{BLE_DEFAULT, BLE_TEST};

// Pins for glider motors
const int GliderMotorPins{};

// Motor type definitions
#define _SERVO 					0x100
#define _DC 					0x101
#define _OTHER 					0x102

// Timing variables
#define SENSOR_POLL_RATE_MS 	100
#define COMM_REFRESH_RATE_MS 	500
#define SYSTEM_DELAY_MS 		5

// Message Variables
#define MSG_START 				0x02
#define MSG_ID_PLANE		 	0x0D
#define MSG_ID_GLIDER 			0x0E
#define MSG_ID_GROUNDSTATION 	0x0F

#endif // CONFIG_H
