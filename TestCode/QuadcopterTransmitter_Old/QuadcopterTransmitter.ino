// Code for circuitboard that is placed on the Joystick (Arduino Uno) and is the "transmitter"
// Changes will still be made once actual quadcopter is finished.
// By Ashish Agrahari

// Include libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

// Define the joystick inputs
#define jB1 2  // Joystick button 1
#define jB2 3  // Joystick button 2
#define j1PotXPin A0 //Joystick 1 axis X
#define j1PotYPin A1 //Joystick 1 axis Y
#define j2PotXPin A2 //Joystick 2 axis X
#define j2PotYPin A3 //Joystick 2 axis Y

// ************ Initialize nRF24L01 variables *****************
RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00010"; // Wireless communication address

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
// Creating package to send data in (must match reciever package):
struct Data_Package {
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
};
Data_Package data; //Create a variable with the above structure

void setup() {
  Serial.begin(115200); // Open serial port

  // Begin radio communication using nRF24L01
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);

  // Activate the Arduino internal pull-up resistors
  pinMode(jB1, INPUT_PULLUP);
  pinMode(jB2, INPUT_PULLUP);

  // Set initial default values
  // Values are from 0 to 255. When Joystick is in resting position (middle), the value is 127.
  // The actual joystick gives 0 to 1023, but we map it to 0 to 255 in order to send one BYTE
  data.j1PotX = 127;
  data.j1PotY = 127;
  data.j2PotX = 127;
  data.j2PotY = 127;
  data.j1Button = 1;
  data.j2Button = 1;
}

void loop() {

  // Read all analog inputs and map them to one Byte value
  // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  data.j1PotX = map(analogRead(j1PotXPin), 0, 1023, 0, 255);
  data.j1PotY = map(analogRead(j1PotYPin), 0, 1023, 0, 255);
  data.j2PotX = map(analogRead(j2PotXPin), 0, 1023, 0, 255);
  data.j2PotY = map(analogRead(j2PotYPin), 0, 1023, 0, 255);

  // Read digital inputs
  data.j1Button = digitalRead(jB1);
  data.j2Button = digitalRead(jB2);

  // Send the data from the structure to the receiver
  radio.write(&data, sizeof(Data_Package));
}
