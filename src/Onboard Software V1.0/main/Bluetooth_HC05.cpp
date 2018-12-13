#include "Arduino.h"
#include "Bluetooth_HC05.h"

// http://forum.arduino.cc/index.php?topic=91707.0


// Reading a bluetooth packet
// TODO: SOP AND EOP need to be hard defines based the message start byte
// TODO: May need to revist based on how it is read from android
char* BluetoothHC05::read(){
    // End of packet
    char SOP = 0x02;
    char EOP = 0x01;

    bool started = false;
    bool ended = false;

    // TODO need to change buffer size based on our needs
    const int dataBufferSize = 80;
    char inData[dataBufferSize];
    byte index = 0;

    // Read all serial data available, as fast as possible
    // TODO remove serial dependency
    // TODO try threading this reading functionality
    while(Serial.available() > 0)
    {
        char inChar = Serial.read();
        if(inChar == SOP)
        {
            index = 0;
            inData[index] = inChar;
            started = true;
            ended = false;
        }

        // TODO: Revisit and fix this
        else if(inChar == EOP)
        {
            // Read message end byte
            inData[index] = inChar;
            index++;

            // Read check sum
            inChar = Serial.read();
            inData[index] = inChar;

            ended = true;
            break;
        }

        else
        {
            if(index < (dataBufferSize - 1))
            {
                inData[index] = inChar;
                index++;
            }
        }
    }

    // We are here either because all pending serial
    // data has been read OR because an end of
    // packet marker arrived. Which is it?
    if(started && ended)
    {
        return inData;
    }

    // TODO handle failing properly
    return "F"
}

// TODO: Write sends bytes print sends strings, does this matter when talking to android?
void BluetoothHC05::write(char buf*){
    Serial.println(buf);
}