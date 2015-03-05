#include "Support.h"

//the executable parts of the support go here.

Support::Support()
{ 
  //Might not have to do anything here. We'll see. For right now, we don't. 
  _ArmStepper = Adafruit_MotorShield(0x61);
  arm = _ArmStepper.getStepper(200, 1); // motor port #1 (M1 & M2), stepper that controls arm up and down
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
