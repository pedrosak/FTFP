#include "Support.h"


//the constructor will take in a pointer to the arm motor
Support::Support(Adafruit_StepperMotor *pointerToArm)
{ 
  
  arm = pointerToArm;

}

//function to move arm. Takes in number of steps and a boolean for up or down.
//A true corresponds to an upward movement, false is down
bool Support::Arm(int steps, bool up)
{
  if(up)
  {
  arm->step(steps,FORWARD,DOUBLE);
  }
  else
  {
  arm->step(steps,BACKWARD,DOUBLE);
  }
 return true; 
}

//function to initialize/do line following
void Support::Follow()
{
  //Not sure how the line following will work. 
}

bool Support::StartUp()
{
 //we'll monitor the  start LED. Perform any POST functions
 
 //return true if all is dandy, false otherwise. If false, system won't start. Throw some error. 
  
}

bool Support::Finish()
{
  
  //call this to stop everything on the robot. Or something to that effect. Cartwheels?
  
}

void Support::Creep()
{
  //move system forward at a very slow rate
}

void Support::Shuffle(float dist) //move system left or right
{
  if(dist<0) //left
  {
    
  }
  else //right
  {
    
    
  }
}
