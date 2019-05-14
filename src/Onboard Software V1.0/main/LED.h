#ifndef LED_H
#define LED_H

/*
 * File Purpose
 *    The purpose of this file is to create a simple interface for turning on and off an led
 *    And for threading led function so that you can make an led blink for a specified amount of duty at any frequency
 */

#include <stdint.h>
#include <TeensyThreads.h>
#include "Runnable.h"

class LED : public Runnable{
private:
	uint8_t pin;
    
	// True means led is ON, false means led is OFF
	bool state;

  // PWM Variables
	float duration;
	float period;
	float duty;

  // Thread object
  std::thread *blinkThread;
	
protected:
  // Runnable function that we need to implement
  void runTarget(void *arg);
    
public:
	LED(uint8_t pin, float duration, float period, float duty);
 	~LED();

  	// Turn on and off LED, volatile for threading use
	void turnOn() volatile;
	void turnOff() volatile;

	// Start thread that will last for duration
	void startBlinking(float duration, float period, float duty);

  	// Getters and setters. State shouldn't be set because its dependent on the state of the LED
	bool getState() const;
	float getDuration() const;
	float getPeriod() const;
	float getDuty() const;
	
	void setDuration(float duration);
	void setPeriod(float period);
	void setDuty(float duty);
};

#endif	// LED_H
