#include <Servo.h> 
#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define DIR1_PIN 4
#define STEP1_PIN 5
#define DIR2_PIN 6
#define STEP2_PIN 7 

int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellPin1 = 1; 
int photocellPin2 = 2;
int photocellPin3 = 3;
int photocellReading;     // the analog reading from the sensor divider
int photocellReading1;
int photocellReading2;
int photocellReading3;

int s1;
int s2;
int pinHolding[] = {photocellPin, photocellPin1, photocellPin2, photocellPin3};
int state[4];
int i = 0;
int currentMax;
int maxPin = 0;

// Create the motor shield object with the default I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
Adafruit_MotorShield AFMStop = Adafruit_MotorShield(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMSbot = Adafruit_MotorShield(0x60); // No jumper closed

// Stepper motors
Adafruit_StepperMotor *myMotor = AFMStop.getStepper(200, 1); // motor port #2 (M3 & M4)
Adafruit_StepperMotor *my2ndMotor = AFMStop.getStepper(200, 2); // motor port #1 (M1 & M2)

// DC Motors
Adafruit_DCMotor *myM1Motor = AFMSbot.getMotor(1);
Adafruit_DCMotor *myM3Motor = AFMSbot.getMotor(3);
Adafruit_DCMotor *myM4Motor = AFMSbot.getMotor(4);
    
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 

  // Rotation
  pinMode(DIR2_PIN, OUTPUT);
  pinMode(STEP2_PIN, OUTPUT); 
 
 // create with the default frequency 1.6KHz .begin()
  AFMStop.begin();
  AFMSbot.begin(1000);
  
  // Stepper Motors
  myMotor->setSpeed(250);  // 200 rpm 
  my2ndMotor->setSpeed(250); 
}
 
void loop(void) {
  
  for (i = 0; i < 4; i++) { 
   state[i] = analogRead(pinHolding[i]);
  } 

  currentMax = state[0];
  maxPin = 0;
  for (i = 0; i < 4; i++) {
    if (state[i] > currentMax) {
      currentMax = state[i];
      maxPin = i;
    }
  }
  
  if (currentMax > 50) { 
  
// Breadboard orientation = +/- on bottom
  if (maxPin == 0) { // Initial position
    Serial.println("yellow"); // Yellow = bottom left
    
    // Move claw down
    myMotor->step(410, BACKWARD, DOUBLE);  // Down
    my2ndMotor->step(200, BACKWARD, DOUBLE); // CCW
    delay(1000); 
   
    // Move claw up
    myMotor->step(410, FORWARD, DOUBLE); // Up
    my2ndMotor->step(200, FORWARD, DOUBLE); // CW
    delay(1000);
  }  
  
  // Green = left of yellow 
  if (maxPin == 1) {
    Serial.println("green"); // Green = top right
    digitalWrite(DIR2_PIN, LOW); // Low = rotate 90 degrees
    for (s2 = 0; s2 < 400; s2++) {
      digitalWrite(STEP2_PIN, LOW);
      digitalWrite(STEP2_PIN, HIGH);
      delayMicroseconds(1000);
    }
    
    // Move claw down
    myMotor->step(410, BACKWARD, DOUBLE);  // Down
    my2ndMotor->step(200, BACKWARD, DOUBLE); // CCW
    delay(1000); 
    
    // Move claw up
    myMotor->step(410, FORWARD, DOUBLE); // Up
    my2ndMotor->step(200, FORWARD, DOUBLE); // CW
    delay(1000);
      
      // Rotate back to yellow while raising the z - direction
      digitalWrite(DIR2_PIN, HIGH);
      for (s2 = 0; s2 < 400; s2++) {
          digitalWrite(STEP2_PIN, LOW);
          digitalWrite(STEP2_PIN, HIGH);
          delayMicroseconds(1000);
          }
      }
  }

  // Red = up from yellow position
  if (maxPin == 2) {
    Serial.println("red"); // Red = top right
    digitalWrite(DIR2_PIN, LOW); // Low = rotate 180 degrees
    for (s2 = 0; s2 < 800; s2++) {
      digitalWrite(STEP2_PIN, LOW);
      digitalWrite(STEP2_PIN, HIGH);
      delayMicroseconds(1000);
    }
    
    // Move claw down
    myMotor->step(410, BACKWARD, DOUBLE);  // Down
    my2ndMotor->step(200, BACKWARD, DOUBLE); // CCW
    delay(1000); 
    
    // Move claw down
    myMotor->step(410, FORWARD, DOUBLE); // Up
    my2ndMotor->step(200, FORWARD, DOUBLE); // CW
    delay(1000);
      
      // Rotate back to yellow while raising the z - direction
      digitalWrite(DIR2_PIN, HIGH);
      for (s2 = 0; s2 < 800; s2++) {
          digitalWrite(STEP2_PIN, LOW);
          digitalWrite(STEP2_PIN, HIGH);
          delayMicroseconds(1000);
          }
      }
  }
  
  // Blue = right of yellow position
  if (maxPin == 3) { // Blue = bottom left
  Serial.println("blue");
    digitalWrite(DIR2_PIN, LOW); // Low = rotate 270 degrees
    for (s2 = 0; s2 < 1200; s2++) {
      digitalWrite(STEP2_PIN, LOW);
      digitalWrite(STEP2_PIN, HIGH);
      delayMicroseconds(1000);
    }
    
    // Move claw down
    myMotor->step(410, BACKWARD, DOUBLE);  // Down
    my2ndMotor->step(200, BACKWARD, DOUBLE); // CCW
    delay(1000); 
    
    // Move claw up
    myMotor->step(410, FORWARD, DOUBLE); // Up
    my2ndMotor->step(200, FORWARD, DOUBLE); // CW
    delay(1000);
      
      // Rotate back to yellow while raising the z - direction
      digitalWrite(DIR2_PIN, HIGH);
      for (s2 = 0; s2 < 1200; s2++) {
          digitalWrite(STEP2_PIN, LOW);
          digitalWrite(STEP2_PIN, HIGH);
          delayMicroseconds(1000);
          }
      }
  }
  }
}
