#include "IMU_MPU6050.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu6050;

//#define OUTPUT_READABLE_YAWPITCHROLL


#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// offsets


//CLASS::CONSTRUCTOR
IMU_MPU6050::IMU_MPU6050() {
  // Constructor
}

float IMU_MPU6050::getYaw() {
    return ypr[0] * 180/M_PI;
}

float IMU_MPU6050::getPitch() {
    return ypr[1] * 180/M_PI;
}

float IMU_MPU6050::getRoll() {
    return ypr[2] * 180/M_PI;
}

void IMU_MPU6050::init(int16_t xa, int16_t ya, int16_t za, int16_t xg, int16_t yg, int16_t zg) {

    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz). Comment this line if having compilation difficulties with TWBR.
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    Serial.begin(115200);

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu6050.initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu6050.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu6050.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu6050.setXGyroOffset(xg);
    mpu6050.setYGyroOffset(yg);
    mpu6050.setZGyroOffset(zg);
    mpu6050.setXAccelOffset(xa);
    mpu6050.setYAccelOffset(ya);
    mpu6050.setZAccelOffset(za); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu6050.setDMPEnabled(true);

        // enable Arduino interrupt detection
        mpuIntStatus = mpu6050.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu6050.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);
}

void IMU_MPU6050::update() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    mpuIntStatus = mpu6050.getIntStatus();

    // get current FIFO count
    fifoCount = mpu6050.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu6050.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else {        // Commented out by 109jb -->  if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu6050.getFIFOCount();

        // read a packet from FIFO
        mpu6050.getFIFOBytes(fifoBuffer, packetSize);

        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;


            // display Euler angles in degrees
            mpu6050.dmpGetQuaternion(&q, fifoBuffer);
            mpu6050.dmpGetGravity(&gravity, &q);
            mpu6050.dmpGetYawPitchRoll(ypr, &q, &gravity);



        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}
