#include <Wire.h>
#include <Adafruit_MotorShield.h>


Adafruit_MotorShield etch = Adafruit_MotorShield(0x61); // Rightmost jumper closed
Adafruit_MotorShield etch2 = Adafruit_MotorShield(0x60);
int STEPS = 68; //number of steps in a revolution for motor



// Stepper motors
Adafruit_StepperMotor *right = etch2.getStepper(68, 1); // motor port #2 (M3 & M4)
Adafruit_StepperMotor *left = etch.getStepper(68, 1); // motor port #1 (M1 & M2)
boolean complete = false;


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  // create with the default frequency 1.6KHz .begin()
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  etch.begin();
  
}

void loop()
{
  
  if(!complete)
  {
   Etch();
  complete = true; 
    
  }
  
  
}

void Etch()
{
  //in this instance, BACKWARD is clockwise and FORWARD is counter clock wise
  //this is with the outer coils on the lower motor controls
  /*
  //I
  right->step(1.5*STEPS,BACKWARD,DOUBLE);
  delay(500);
  right->step(1.5*STEPS,FORWARD,DOUBLE);
  */
  //3 Es
  for(int i = 0; i<3; i++)
  {
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
    delay(500);
    right->step(1.5*STEPS,BACKWARD,DOUBLE);
    delay(500);
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
    delay(500);
    left->step(0.5*STEPS,FORWARD,DOUBLE);
    delay(500);
    right->step(0.75*STEPS,FORWARD,DOUBLE);
    delay(500);
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
    delay(500);
    left->step(0.5*STEPS,FORWARD,DOUBLE);
    delay(500);
    right->step(0.75*STEPS,FORWARD,DOUBLE);
    delay(500);
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
  }
  
  
  
}
