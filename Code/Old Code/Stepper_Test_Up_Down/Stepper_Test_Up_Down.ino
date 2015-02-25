/* 

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

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

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  // create with the default frequency 1.6KHz .begin()
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  AFMStop.begin();
  AFMSbot.begin(1000);
  
  // Stepper Motors
  myMotor->setSpeed(250);  // 200 rpm 
  my2ndMotor->setSpeed(250);

  // DC Motors
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

void loop() {
  //Serial.println("Single coil steps");
  //myMotor->step(200, BACKWARD, SINGLE); // Up
  //myMotor->step(50, FORWARD, SINGLE);  // Down
 
  Serial.println("Double coil steps");
  myMotor->step(410, FORWARD, DOUBLE); // Up
  my2ndMotor->step(200, FORWARD, DOUBLE); // CW
  delay(1000);
  myMotor->step(410, BACKWARD, DOUBLE);  // Down
  my2ndMotor->step(200, BACKWARD, DOUBLE); // CCW
  delay(1000); 
  //Serial.println("Interleave coil steps");
  //myMotor->step(300, BACKWARD, INTERLEAVE); // Up
  //myMotor->step(300, FORWARD, INTERLEAVE);  // Down
   
  //Serial.println("Microstep steps");
  //myMotor->step(200, BACKWARD, MICROSTEP); // Up
  //myMotor->step(200, FORWARD, MICROSTEP);  // Down
}
