#include "Support.h"


//the constructor will take in a pointer to the arm motor
Support::Support(Adafruit_StepperMotor *pointerToArm, Adafruit_DCMotor *pointerToLeft, Adafruit_DCMotor *pointerToBack, Adafruit_DCMotor *pointerToRight, int *pointerToEncoderPins)
{ 
  
  arm = pointerToArm;
  leftMotor = pointerToLeft;
  backMotor = pointerToBack;
  rightMotor = pointerToRight;
  encoderPins = pointerToEncoderPins;

}

//function to move arm. Takes in number of steps and a boolean for up or down.
//A true corresponds to an upward movement, false is down
bool Support::Arm(int steps, bool down)
{
  if(down)
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

void Support::Shuffle(int dist) //move system left or right
{
  //local variable to keep track of how far the encoder has moved
  int encoderPos = 0;
  int encoderPinALast = LOW;
  int n = LOW;
  int encoderPinA = encoderPins[2];
  int encoderPinB = encoderPins[3];
  
  if(dist>0) //right
  {
    backMotor->run(FORWARD); 
  }
  else //left
  {
    backMotor->run(BACKWARD);
  }

  backMotor->setSpeed(100);
  
  //while our encoder position is less than our distance we need to move
  while(abs((float)encoderPos)<abs(dist))
  {
     n = digitalRead(encoderPinA);
     if((encoderPinALast == LOW) && (n==HIGH))
     {
      if(digitalRead(encoderPinB)==LOW)
      {
       encoderPos--; 
      }
      else
      {
       encoderPos++;
      }
     }
     encoderPinALast = n;
  }
  backMotor->run(RELEASE);
  
  return;
}


void Support::BackForward(int dist) //move the system forward or backward
{
    //local variable to keep track of how far the encoder has moved
  int encoderPos = 0;
  int encoderPinALast = LOW;
  int n = LOW;
  int encoderPinA;
  int encoderPinB;
  
  if(dist>0) //forward
  {
    leftMotor->run(BACKWARD); 
    rightMotor->run(FORWARD);
    encoderPinA = encoderPins[0];
    encoderPinB = encoderPins[1];
  }
  else //backward
  {
    leftMotor->run(FORWARD); 
    rightMotor->run(BACKWARD);
    encoderPinA = encoderPins[4];
    encoderPinB = encoderPins[5];
  }

  leftMotor->setSpeed(100);
  rightMotor->setSpeed(100);
  
  //while our encoder position is less than our distance we need to move
  while(abs((float)encoderPos)<abs(dist))
  {
     n = digitalRead(encoderPinA);
     if((encoderPinALast == LOW) && (n==HIGH))
     {
      if(digitalRead(encoderPinB)==LOW)
      {
       encoderPos--; 
      }
      else
      {
       encoderPos++;
      }
     }
     encoderPinALast = n;
  }
    leftMotor->run(RELEASE); 
    rightMotor->run(RELEASE);
  
  return;
  
  
  
}
