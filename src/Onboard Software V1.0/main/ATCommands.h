#ifndef AT_COMMANDS_H
#define AT_COMMANDS_H

// Finish AT Command String
char *ATEnd = "\r\n";

// Firmware Version String
char *ATVersion = "AT+VERSION?";

// Restore to Default String
char *ATDefault = "AT+ORGL";

// Get Module Address String
char *ATModuleAddr = "AT+ADDR?";

// Set Module Name String. Need to add specific name after command
char *ATSetModuleName = "AT+NAME=";

// Get Module Name String
char *ATGetModuleName = "AT+NAME?";

// Check Full Status String
// 1 is RSSI, 1 number of devices, 48 is timeout
char *ATCheckStatus = "AT+INQM=1,9,48";
// Query Devices For Status String
// Response is Address, Device Class, RSSI
char *ATQueryStatus = "AT+INQ";

// Set Password String. Need to add password string after
char *ATSetPswd = "AT+PSWD=";

// Get Password String
char *ATGetPswd = "AT+PSWD?";

// TODO: Do we need Connect/Disconnect?

#endif // AT_COMMANDS_H