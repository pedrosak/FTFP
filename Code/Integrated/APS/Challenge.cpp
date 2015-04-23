#include "Challenge.h"

Challenge::Challenge(Support *support, Adafruit_PWMServoDriver *servoShield, int maxMinValues[])
{

  //initialization of Simon
  photocellPin = 0; // the cell and 10K pulldown are connected to a0
  photocellPin1 = 1;
  photocellPin2 = 2;
  photocellPin3 = 3;

  _support = support;
  _servoShield = servoShield;
  _maxMinValues = maxMinValues;

}

/*
This function will twist the Rubik's cube. The # of steps is half of
 the number of steps in the stepper motor. We pass this function a 
 pointer to the stepper motor
 */
bool Challenge::Rubiks(Adafruit_StepperMotor *rubiks)
{

  _support->Arm(80,true); //lower arm to cube
  rubiks->step(125,FORWARD,DOUBLE); //twist 180
  _support->Arm(80,false); //return arm to native position
  rubiks->step(75,FORWARD,DOUBLE); //twist 180
  rubiks->release(); //release so that we don't keep using power
  return true;

}

/*
This function will play Etch a sketch. We pass it a pointer to the stepper motors it will be using
 */
bool Challenge::Etch(   Adafruit_StepperMotor *left,    Adafruit_StepperMotor *right, int STEPS)
{
  _support->Arm(200,true); //lower the arm to etch
  //I
  right->step(1.5*STEPS,BACKWARD,DOUBLE);
  right->step(1.5*STEPS,FORWARD,DOUBLE);
  right->release();
  
  //3 Es
  for(int i = 0; i<3; i++)
  {
    Serial.println("E");
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
    left->release();
    right->step(1.5*STEPS,BACKWARD,DOUBLE);
    right->release();
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
    left->step(0.5*STEPS,FORWARD,DOUBLE);
    left->release();
    right->step(0.75*STEPS,FORWARD,DOUBLE);
    right->release();
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
    left->step(0.5*STEPS,FORWARD,DOUBLE);
    left->release();
    right->step(0.75*STEPS,FORWARD,DOUBLE);
    right->release();
    left->step(0.5*STEPS,BACKWARD,DOUBLE);
    left->release();
  }
      left->step(0.5*STEPS,BACKWARD,DOUBLE);
  _support->Arm(200,false); //return arm to native position

  return true;

}

/*
This is the function to play simon. It will get a calibration for
 each photocell, and then press the center button. From here, it 
 will read the lights until 15 seconds has been reached. After, it
 will raise the arm and exit the function
 */
bool Challenge::Simon()
{
  initializeServo();
  int pinHolding[] = {
    photocellPin, photocellPin1, photocellPin2, photocellPin3
  }; 

  boolean start = false;
  int oldCounter = 0;

  _support->Arm(100,true); //lower arm to Simon
  startSimon(pinHolding,4);
  unsigned long time = millis(); //get current time processor has been running
  while((millis()-time)<=(unsigned long)(15*1000)) //if current time minus our beginning time stamp is less than 15 seconds
  {
    for (int i = 0; i < 4; i++)
    {
      int reading = analogRead(pinHolding[i]);
      if (reading - cellThresholds[i] > LIT_THRESHOLD) //if the reading minus its calibration is greater than some brightness
      {
        colorSequence.push(i + 1); //add the correct servo to actuate to the sequence
        start = true; //signal we've started playing
        while (reading - cellThresholds[i] > LIT_THRESHOLD ) //while that same color is still high, block
        {
          reading = analogRead(pinHolding[i]);
        }
      }
    }

    if ((colorSequence.count() == (oldCounter+1)) && start) //if we have one more in our color sequence vs last time we played
    {
      oldCounter = colorSequence.count(); //change the value
      Play(&colorSequence); //play
      start = false;
    }
  }
  _support->Arm(100,false); //return arm to native position
  return true;

}

bool Challenge::Card()
{


  _support->Arm(200,false); 
  //really, this is all there is to the challenge.......


  _support->Arm(200,true);
  //return true if the system didn't encounter any issues.

  return true;
}

/*
This function will "Play" Simon. We pass it a queue array of
 the buttons to push. It will pop off each element, calling
 actuate servo each time, until the array is empty
 */
void Challenge::Play(QueueArray<int> *colorSequence)
{
  while (!colorSequence->isEmpty())
  {
    actuateServo(colorSequence->pop());
  }
}

/*
This function will actuate each servo on simon. We pass it the
 servo to actuate, and it actuates it. Easy-peasy.
 */
void Challenge::actuateServo(int servoNum)
{
  /*
    Current simon says interrector : Version 1 (2 by 4 and hammer version)
   All 4 Micro servos have been tested. Center servo is not mounted and still
   missing Max/Min (Kurt, March 29)
   
   use this function to actuate the servo.
   servo numbering scheme:
   blue - 0
   red - 1
   green - 2
   yellow - 3
   center - 4
   */

  //Fetches servos min and max from maxMinValues array.
  int SERVOMIN = *(_maxMinValues+servoNum*2);
  int SERVOMAX = *(_maxMinValues+servoNum*2+1);

  //Bring push rod back up to starting posistion.
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) 
  {
    _servoShield->setPWM(servoNum, 0, pulselen);
  }

  //Push pushrod downwards.
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) 
  {
    _servoShield->setPWM(servoNum, 0, pulselen);
  }

}

/*
This function will start the simon game. It does this by calibrating
 each photocell to its environment, and then pressing the center button;
 */
void Challenge::startSimon(int pinHolding[], int length)
{
  for (int i = 0; i < length; i++)
  {
    Average<int> ave(100);
    for (int j = 0; j < 100; j++)
    {

      ave.push(analogRead(pinHolding[i]));
    }
    cellThresholds[i] = ave.mode();
  }
  actuateServo(0);
}

//Initializes servo to up position
//Need to add a 5th servo for center servo which has not been installed yet (kurt)
void Challenge::initializeServo() 
{

  for(int z = 5; z >=0; z--) 
  {
    int minVals = *(_maxMinValues+z*2);
    int maxVals = *(_maxMinValues+z*2+1);
    for (uint16_t pulselen = minVals; pulselen < maxVals; pulselen++) 
    {
      _servoShield->setPWM(z, 0, pulselen);
    }
  }

}




