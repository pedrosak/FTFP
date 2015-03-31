#ifndef Support_h
#define Support_h
#endif // Support_h
#include <Adafruit_MotorShield.h>
#include <Wire.h>

//this class is intended to be used for support functions (i.e. moving the arm, line follow)
//functions that have no home otherwise.

class Support
{
public:
   Support(Adafruit_StepperMotor *pointerToArm, Adafruit_DCMotor *leftMotor, Adafruit_DCMotor *backMotor, Adafruit_DCMotor *rightMotor, int *encoderPins);
   bool Arm(int steps, bool up);
   void Follow();
   bool StartUp();
   bool Finish();
   void Creep();
   void Shuffle(int dist);
   void BackForward(int dist);
private:
  Adafruit_StepperMotor *arm; //pointer to the arm motor. Will be set in the constructor
  Adafruit_DCMotor *leftMotor; //pointer to the left drive motor. Will be set in the contrustor
  Adafruit_DCMotor *backMotor; //pointer to the back drive motor. Will be set in the constructor
  Adafruit_DCMotor *rightMotor; //pointer to the right drive motor. Will be set in the constructor
  int *encoderPins; //array of pins that correspond to encoders to each motor

};
