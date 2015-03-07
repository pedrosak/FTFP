#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Wire.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Stepper motors
Adafruit_StepperMotor *left = AFMS.getStepper(48, 1); // motor port #1 (M1 & M2)
Adafruit_StepperMotor *right = AFMS.getStepper(48, 2); // motor port #2 (M3 & M4)


void setup(){
 Serial.begin(9600);
 //rotation.setSpeed(10);
 AFMS.begin(1000);
left ->setSpeed(48);
right->setSpeed(48);
 
}

void loop(){


 
left->step(132, FORWARD, DOUBLE); // 2 full rotations
delay(1000);
//midpoint left
left->step(24, BACKWARD, DOUBLE); //go back a little for last E

//E going down
right->step(12, BACKWARD, DOUBLE);
delay(1000);
left->step(24, FORWARD, DOUBLE);
delay(1000);
left->step(24, BACKWARD, DOUBLE);
delay(1000);
right->step(12, BACKWARD, DOUBLE);
delay(1000);
left->step(24, FORWARD, DOUBLE);
delay(1000);
left->step(24, BACKWARD, DOUBLE);

//space for letter and next E
left->step(28, BACKWARD, DOUBLE);

//going up second  E

right->step(12, FORWARD, DOUBLE);
delay(1000);
left->step(24, FORWARD, DOUBLE);
delay(1000);
left->step(24, BACKWARD, DOUBLE);
delay(1000);
right->step(12, FORWARD, DOUBLE);
delay(1000);
//go back down
right->step(24, BACKWARD, DOUBLE);

//space for first E
left->step(28, BACKWARD, DOUBLE);
//going up first E
right->step(12, FORWARD, DOUBLE);
left->step(24, FORWARD, DOUBLE);
left->step(24, BACKWARD, DOUBLE);
right->step(12, FORWARD, DOUBLE);
//go back down
right->step(24, BACKWARD, DOUBLE);
delay(1000);

//I
//space
left->step(4, BACKWARD, DOUBLE);
delay(1000);

left->step(24, BACKWARD, DOUBLE);
delay(1000);
//go up on I
right->step(24, FORWARD, DOUBLE);
delay(1000);
right->step(24, BACKWARD, DOUBLE);
delay(1000);

left->step(24, BACKWARD, DOUBLE);



}
