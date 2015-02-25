/*
Motor Control
Three motors $ omni wheels for the Autonomous Panda System
set to move in the forward and reverse directions based on 
serial input from the computer.

Based on Adafruit Motorshield tutorial "DCMotorTest"

Mary Luongo
28 OCT 2014
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myM1Motor = AFMS.getMotor(1);
Adafruit_DCMotor *myM3Motor = AFMS.getMotor(3);
Adafruit_DCMotor *myM4Motor = AFMS.getMotor(4);
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // begin 9600 Baud rate
  AFMS.begin(1000); // begin freq. 1kHz (M3 & M4 can only go up to 1kHz)
  myM1Motor->setSpeed(0); // M1 speed at the start is zero (off)
  myM1Motor->run(FORWARD);
  // turn on motor
  myM1Motor->run(RELEASE); 
  
  myM3Motor->setSpeed(0); // M3 speed at the start is zero (off)
  myM3Motor->run(FORWARD);
  // turn on motor
  myM3Motor->run(RELEASE);
  
  myM4Motor->setSpeed(0); // M4 speed at the start is zero (off)
  myM4Motor->run(FORWARD);
  // turn on motor
  myM4Motor->run(RELEASE); 
}

// the loop function runs over and over again forever
int incomingByte = 0; // M1 control
int incomingByte2 = 0; // M3 control
int incomingByte3 = 0; // M4 control

void loop() {
  
   if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.parseInt();
                incomingByte2 = Serial.parseInt();
                incomingByte3 = Serial.parseInt();
                if (incomingByte >= 0) { // M1 forward speed
                  myM1Motor->run(FORWARD); 
                  myM1Motor->setSpeed(incomingByte); 
                 }
                if (incomingByte < 0) {   // M1 backward speed
                  myM1Motor->run(BACKWARD); 
                  myM1Motor->setSpeed(abs(incomingByte)); 
                 }
                if (incomingByte2 >= 0) { // M3 forward speed
                  myM3Motor->run(FORWARD); 
                  myM3Motor->setSpeed(incomingByte2); 
                 }
                if (incomingByte2 < 0) { // M3 backward speed
                  myM3Motor->run(BACKWARD); 
                  myM3Motor->setSpeed(abs(incomingByte2)); 
                 }
                if (incomingByte3 >= 0) { // M4 forward speed
                  myM4Motor->run(FORWARD); 
                  myM4Motor->setSpeed(incomingByte3); 
                 }
                if (incomingByte3 < 0) {  // M4 backward speed
                  myM4Motor->run(BACKWARD); 
                  myM4Motor->setSpeed(abs(incomingByte3)); 
                 }
               
                Serial.read();
  }
  
}
