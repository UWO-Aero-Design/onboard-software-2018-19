#ifndef CONFIG_H
#define CONFIG_H

/*
 * File Purpose
 *    The purpose of this file is to accumulate all configuration variables
 *    Having magic numbers is not good programming practice so use this to typedef and replace system magic numbers
 */

// As of Onboard PCB V1.0, these are the pin mappings for the LEDs
// Blue = 27, Green = 28, Yellow = 29, Red = 30
enum LEDPIN{BLUE_LED = 27, GREEN_LED, YELLOW_LED, RED_LED};

#endif // CONFIG_H
