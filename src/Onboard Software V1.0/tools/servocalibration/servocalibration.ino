#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  115 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // this is the 'maximum' pulse length count (out of 4096)

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pwm.begin();
pwm.setPWMFreq(50);

delay(10);
}

const int SERVOMINCHANNEL = 8, SERVOMAXCHANNEL = 15;
int channel = 0, deg = 0, pulse = 0;
bool stringComplete = false, runServo = false, printmsg = true;

void loop() {

  if(printmsg) { 
    //printInput();
    printmsg = false;
  }

  if(runServo) {
    pwm.setPWM(channel, 0, pulse);
    Serial.print("Channel: ");
    Serial.print(channel);
    Serial.print(" | Degrees: ");
    Serial.print(deg);
    Serial.print(" | Pulse: ");
    Serial.println(pulse);
    runServo = false;
    printmsg = true;
  }

}

void serialEvent() {
  String inputString = "";
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  int space = inputString.indexOf(',');
  channel = inputString.substring(0, space).toInt();
  deg = inputString.substring(space + 1).toInt();

  pulse = map(deg, 0, 180, SERVOMIN, SERVOMAX);

  inputString = "";

  if((channel >= SERVOMINCHANNEL && channel <= SERVOMAXCHANNEL) && (deg >= 0 && deg <= 180)) runServo = true;
  else Serial.println("Invalid entry. Try again.");

}

void printInput() {
  Serial.print("Enter channel(");
  Serial.print(SERVOMINCHANNEL);
  Serial.print("-");
  Serial.print(SERVOMAXCHANNEL);
  Serial.println("),degrees(0-180)");
}
