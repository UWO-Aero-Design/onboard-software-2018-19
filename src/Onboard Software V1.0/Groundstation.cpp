#include "Groundstation.h"

// Constructor for the groundstation
Groundstation::Groundstation(){
	this.sysTyp = SYS_GROUNDSTATION;
}

void Groundstation::init(){
	radio.init(sysTyp, RADIO_MASTER);
	bluetooth.init(sysTyp, BLE_DEFAULT);
}

// Function that is called on every system loop. Main control of the system type
void Groundstation::update(){

	commCurrMs = millis();
	if(commCurrMs - commPrevMs >= COMM_REFRESH_RATE_MS){
		commPrevMs = commCurrMs;

		{
			int command = msgParse.verifyMsg(radio.recv());
			bluetooth.send(radio.getBuffer());
		}

		{
			command = msgParse.verifyMsg(bluetooth.recv());
			radio.send(bluetooth.getBuffer());
		}
		
	}

	delay(SYSTEM_DELAY_MS);

}