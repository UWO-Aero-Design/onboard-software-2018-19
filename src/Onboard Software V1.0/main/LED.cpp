/*
 * File Purpose
 *    Implementing LED.h functions
 */
 
#include "Arduino.h"
#include "LED.h"
 
// Initial constructor. Sets the pin, pinmode, and sets initial state as false
LED::LED(uint8_t pin, float duration, float period, float duty)
{
	this->pin = pin;
	state = false;
	pinMode(pin, OUTPUT);

	this->duration = duration;
	this->period = period;
	this->duty = duty;

}

LED::~LED()
{
	// TODO: Remove pin from std::vector and clean up threads
}

// TODO: Use efficient digital write not the arduino version
// Turns on the LED and changes state to true
// Volatile for threading, no compiler optimzations
void LED::turnOn() volatile
{
	digitalWrite(pin, HIGH);
	state = true;
}

// TODO: Use efficient digital write not the arduino version
// Turns off the LED and changes state to false
// Volatile for threading, no compiler optimzations
void LED::turnOff() volatile
{
	digitalWrite(pin, LOW);
	state = false;
}

// This function emulates a PWM signal. But used not for controlling voltage but blinking. 
void LED::runTarget(void *arg)
{
  // Casting the derived object so it can be used within the static runnable functions
	LED* thisobj = static_cast<LED*>(arg);

  float elapsedDuration = duration;
  
	do
	{
    // Need threads.delay instead of delay
		thisobj->turnOn();
		threads.delay(period * (duty / 100));
		thisobj->turnOff();
	  threads.delay((period * (1 - (duty / 100))));

    elapsedDuration -= period;
	} while(elapsedDuration > 0);
}
	
// Start thread that will last for duration duration, period period, and duty duty
void LED::startBlinking(float duration, float period, float duty)
{
	this->duration = duration;
	this->period = period;
	this->duty = duty;

  // Creating new thread object will start it. Detach it makes it independent
	blinkThread = new std::thread(&Runnable::runThread, this);
  blinkThread->detach();
}

// Get state
bool LED::getState() const
{
	return state;
}

// Get duration
float LED::getDuration() const
{
	return duration;
}

// Get period
float LED::getPeriod() const
{
	return period;
}

// Get duty
float LED::getDuty() const
{
	return duty;
}

// Set duration
void LED::setDuration(float duration){
	this->duration = duration;
}

// Set period
void LED::setPeriod(float period){
	this->period = period;
}

// Set duty
void LED::setDuty(float duty){
	this->duty = duty;
}
