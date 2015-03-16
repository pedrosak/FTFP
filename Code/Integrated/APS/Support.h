#ifndef Support_h
#define Support_h
#endif // Support_h
#include <Adafruit_MotorShield.h>

//this class is intended to be used for support functions (i.e. moving the arm, line follow)
//functions that have no home otherwise.

class Support
{
public:
   Support(Adafruit_StepperMotor *pointerToArm);
   bool Arm(int steps, bool up);
   void Follow();
   bool StartUp();
   bool Finish();
   void Creep();
   void Shuffle(float dist);
private:
  Adafruit_StepperMotor *arm; //pointer to the arm motor. Will be set in the constructor
  
  
};
