#ifndef RECEIVER_H
#define RECEIVER_H

extern "C" {
	volatile int pins[] = {23, 22, 21, 20, 5, 4};
	volatile int pwmRead[] = {1, 1, 1, 1, 1, 1};
	volatile long pwmTime[] = {0, 0, 0, 0, 0, 0};

	void pwm0() {
		if (digitalRead(pins[0]) == HIGH) {
			pwmTime[0] = micros();
		} else {
			pwmRead[0] = micros() - pwmTime[0];
		}
	}	
}

#endif // RECEIVER_H
