// Code for circuitboard that is placed on the quadcopter (Arduino Nano) and is the "reciever"

// Include libraries
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

// Defining motor pins
#define Motor1Pin 3
#define Motor2Pin 5
#define Motor3Pin 9
#define Motor4Pin 10

// ************ Initialize nRF24L01 variables *****************
RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00010"; // Wireless communication address
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
// Creating package to recieve data in:
struct Data_Package {
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
};
Data_Package data; //Create a variable with the above structure

// ************ Initialize MPU6050 variables *****************
MPU6050 mpu;

#define INTERRUPT_PIN 2  // specific interrupt pin on Arduino nano every

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}

void setup() {
  Serial.begin(9600); // Open serial port
  // Note: Baud rate at 115200 will make Serial fasterr but they will print out MPU slower than the joystick

  // Begin radio communication using nRF24L01
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); //  Set the module as receiver
  resetData(); // Initally reset all joystick input values

  // ************ MPU6050 setup *****************

  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  //Wire.setWireTimeout(3000, true); // VERY IMPORTANT!!! THIS FIXES THE I2C BUS FROM HANGING
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  while (!Serial); // wait for Leonardo enumeration, others continue immediately

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP (Digital motion processor (on MPU))
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // set gyro offsets
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788);

  // make sure the MPU initialization worked (returns 0 if so)
  if (devStatus == 0) {

    // Generate offsets and calibrate MPU
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();

    // turn on the DMP
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
    Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
    Serial.println(F(")..."));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set DMP as "ready"
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size
    packetSize = mpu.dmpGetFIFOPacketSize();

  } else {
    // There is an error! See the output and debug.
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}
void loop() {

  // if MPU failed don't try to do anything
  if (!dmpReady) return;

  // read a packet from FIFO
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
//    Serial.print("ypr\t");
//    Serial.print(ypr[0] * 180 / M_PI);
//    Serial.print("\t");
//    Serial.print(ypr[1] * 180 / M_PI);
//    Serial.print("\t");
//    Serial.print(ypr[2] * 180 / M_PI);
  }

  // Check whether there is data to be received
  if (radio.available()) {
    // Read the whole incoming data package and store it into the 'data' structure
    radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis();
  }
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is >1 second since we have recived the last data, it has lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior.
    // For example: if a drone has a throttle up and we lose connection, it can keep flying until we reset the values
  }
  // Print the joystick data that is recieved in the Serial Monitor
//  Serial.print("; j1PotX: ");
//  Serial.print(data.j1PotX);
//  Serial.print("; j1PotY: ");
//  Serial.print(data.j1PotY);
//  Serial.print("; j2PotX: ");
//  Serial.print(data.j2PotX);
//  Serial.print("; j2PotY: ");
//  Serial.print(data.j2PotY);
//  Serial.print("; J1Button: ");
//  Serial.print(data.j1Button);
//  Serial.print("; J2Button: ");
//  Serial.print(data.j2Button);
//  Serial.println("");

  // Adjust motor speed based on joystick input.
  // Analog is between 0-255 (which is also what the is being inputted into it from the data structure)
  // For testing purposes, 1 axis controls the all motor speeds.
  // Later on, changes will be made so that another axis will decide to make the quadcopter 
  //      go forwards or backwards and adjust motor speeds accordingly, etc.
  // MPU code will also be more intergrated into this in order to balance the quadcopter and also make sure it doesn't tilt too much, etc.
  analogWrite(Motor1Pin, data.j1PotY);
  analogWrite(Motor2Pin, data.j1PotY);
  analogWrite(Motor3Pin, data.j1PotY);
  analogWrite(Motor4Pin, data.j1PotY);
}
void resetData() {
  // Reset the values when there is no radio connection
  data.j1PotX = 0;
  data.j1PotY = 0;
  data.j2PotX = 0;
  data.j2PotY = 0;
  data.j1Button = 1;
  data.j2Button = 1;
}
