#ifndef LED_H
#define LED_H

//https://github.com/maniacbug/StandardCplusplus/blob/master/examples/string_vector/string_vector.ino
#include <StandardCplusplus.h>
#include <vector>

#include <stdint.h>

#include "Runnable.h"

class LED : public Runnable{
private:
	uint8_t pin;
    
	// True means led is ON, false means led is OFF
	bool state;
	
	float duration;
	float period;
	float duty;
	
	std::thread blinkThread;
	
	// Used to store all intialized LED pins. Cannot make a new LED object that already is tied to the same pins. 
	// Could do in seperate class but functionality is straight forward
	static std::vector<uint8_t> LEDS;
	
	// Initialize in CPP
	//std::vector<uint_8> LED::LEDS = {};
	
protected:
    void runTarget(void *arg);
    
public:
	LED(uint8_t pin);
    ~LED();

	void turnOn() volatile;
	void turnOff() volatile;
	
	// Start thread with no defined duration. Will thread until told to cancel
	void endlessBlinking(float period, float duty);
	
	// Start thread that will last for duration
	void startBlinking(float period, float duration, float duty);
	
	// Wrapper for thread.join. Wait for thread to finish execution before passing by this function call
	void waitForBlinking();
	
	// Stop thread
	void stopBlinking();

	bool getState() const;
	
	float getDuration() const;
	float getPeriod() const;
	float getDuty() const;
	
	void setDuration(float duration);
	void setPeriod(float period);
	void setDuty(float duty);
};



#endif
