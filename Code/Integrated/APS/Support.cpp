#include "Support.h"


//the constructor will take in a pointer to the arm motor
Support::Support(Adafruit_StepperMotor *pointerToArm, Adafruit_DCMotor *pointerToLeft, Adafruit_DCMotor *pointerToBack, Adafruit_DCMotor *pointerToRight, int *pointerToEncoderPins, QTRSensorsRC *pointerToSensors, unsigned int pointerToSensorVals[])
{ 
  
  arm = pointerToArm;
  leftMotor = pointerToLeft;
  backMotor = pointerToBack;
  rightMotor = pointerToRight;
  encoderPins = pointerToEncoderPins;
  sensors = pointerToSensors;
  sensorValues = pointerToSensorVals;
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
  unsigned int position;
  int lastOutput = 0;
  int output = 0;
  int error = 0;
  int pidOutput = 0;
  int lastError = 0;
  
  while(1)
  {
  position = sensors->readLine(sensorValues);
  error = position - 3360;
  pidOutput = ((0.1)*error) + (0.8*(error - lastError));
  output = pidOutput + output;
  lastError = error;
  
  move(output); 
  }
  return;
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

int Support::move(int output)
{
  leftMotor->setSpeed(5+ abs(output));
  rightMotor->setSpeed(5 -abs(output));
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  Serial.println(output);
}

