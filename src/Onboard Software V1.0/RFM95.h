#ifndef RFM95_H
#define RFM95_H

#include <SPI.h>
#include <RH_RF95.h>

// Define SPI pins based on board type
#if defined(TEENSYDUINO)
  #define RFM95_RST     9   
  #define RFM95_CS      10   
  #define RFM95_INT     4   
  #define LED           15
  #define MODE          0x00
#else 
  #define RFM95_RST     2
  #define RFM95_CS      4
  #define RFM95_INT     3
  #define MODE          0x01
  #define LED           13
#endif

// Define radio frequency [hz] and power [db]
#define RF95_FREQ	915.0
#define RF_TX_POWER	23	



class RFM95{
  private:
  	RH_RF95 *rfm95_radio;
  	uint8_t recBuffer[RH_RF95_MAX_MESSAGE_LEN];		// Defining the receiving buffer, should be private
  	uint8_t recBufferLen = sizeof(recBuffer);		// Store buffer length

  public:
  	RFM95();
  	bool init();
  	virtual bool update();

    
};

#endif // PLANE_H
