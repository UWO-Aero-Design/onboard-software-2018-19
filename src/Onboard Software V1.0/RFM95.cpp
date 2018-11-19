#include "RFM95.h"

RFM95::RFM95(){
	//rfm95_radio = new rf95(RFM95_CST, RFM95_INT);
}

bool RFM95::init(){
	rfm95_radio = new rf95(RFM95_CST, RFM95_INT);

	pinMode(RFM95_RST, OUTPUT);
	digitalWrite(RFM95_RST, HIGH);

	// Manually reset radio device
 	digitalWrite(RFM95_RST, LOW);
 	delay(10);
 	digitalWrite(RFM95_RST, HIGH);
 	delay(10);

 	while (!rfm95_radio.init()) {
    	Serial.println("LoRa radio init failed");
    	while (true);
  	}

  	Serial.println("LoRa radio init OK!");

  	// Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
	if (!rfm95_radio.setFrequency(RF95_FREQ)) {
    	Serial.println("setFrequency failed");
		while (1);
  	}
  
  	Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  	rfm95_radio.setTxPower(23, false);
}