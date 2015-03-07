#include "Challenge.h"

Challenge::Challenge(char EtchPort)
{

  //initialization of Simon
  photocellPin = 0; // the cell and 10K pulldown are connected to a0
  photocellPin1 = 1;
  photocellPin2 = 2;
  photocellPin3 = 3;

  LIT_THRESHOLD = 100;

  PRESS_ANGLE = 50; //angle at which servo will actuate to press button
  REST_ANGLE = 100; //angle at which servo will rest

  servoCenter.attach(10);
  servoRed.attach(10);
  servoBlue.attach(10);
  servoYellow.attach(10);
  servoGreen.attach(10);
  servoCenter.write(REST_ANGLE);
  servoRed.write(REST_ANGLE);
  servoBlue.write(REST_ANGLE);
  servoYellow.write(REST_ANGLE);
  servoGreen.write(REST_ANGLE);

  //initialization of Etch
  _Etch = Adafruit_MotorShield(EtchPort);
  _Rubiks = Adafruit_MotorShield(0x61);
  left = _Etch.getStepper(48, 1); // motor port #1 (M1 & M2), stepper that controls left knob on Etch-a-Sketch
  right = _Etch.getStepper(48, 2); // motor port #2 (M3 & M4) stepper that controls right knob on Etch-a-Sketch
  rubiks = _Rubiks.getStepper(200,2); // motor port #2 (M3 & M4) stepper that controls Rubiks


}

/*
This function will twist the Rubik's cube. The # of steps is half of
the number of steps in the stepper motor.
*/
bool Challenge::Rubiks()
{

  _support.Arm(200,false); //lower arm to cube
  rubiks->step(100,FORWARD,DOUBLE);
  _support.Arm(200,true); //return arm to native position
  return true;

}

/*
This function will play Etch a sketch.
*/
bool Challenge::Etch()
{

  _support.Arm(200,false); //lower the arm to etch

  left->step(132, FORWARD, DOUBLE); // 2 full rotations
  //midpoint left
  left->step(24, BACKWARD, DOUBLE); //go back a little for last E

    //E going down
  right->step(14, BACKWARD, DOUBLE);
  left->step(24, FORWARD, DOUBLE);
  left->step(24, BACKWARD, DOUBLE);
  right->step(14, BACKWARD, DOUBLE);
  left->step(24, FORWARD, DOUBLE);
  left->step(24, BACKWARD, DOUBLE);

  //space for letter and next E
  left->step(28, BACKWARD, DOUBLE);

  //going up second  E

    right->step(14, FORWARD, DOUBLE);
  left->step(24, FORWARD, DOUBLE);
  left->step(24, BACKWARD, DOUBLE);
  right->step(15, FORWARD, DOUBLE);
  //go back down
  right->step(29, BACKWARD, DOUBLE);

  //space for first E
  left->step(28, BACKWARD, DOUBLE);
  //going up first E
  right->step(14, FORWARD, DOUBLE);
  left->step(24, FORWARD, DOUBLE);
  left->step(24, BACKWARD, DOUBLE);
  right->step(15, FORWARD, DOUBLE);
  right->step(29, BACKWARD, DOUBLE);

  //I
  //space
  left->step(4, BACKWARD, DOUBLE);

  left->step(24, BACKWARD, DOUBLE);
  //go up on I
  right->step(29, FORWARD, DOUBLE);
  right->step(29, BACKWARD, DOUBLE);
  left->step(28, BACKWARD, DOUBLE);

  _support.Arm(200,true); //return arm to native position

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

  int pinHolding[] = {
    photocellPin, photocellPin1, photocellPin2, photocellPin3
  }; 
  boolean start = false;
  int oldCounter = 0;

  _support.Arm(200,false); //lower arm to Simon
  startSimon(pinHolding,4);
  unsigned long time = millis();

  while((time-millis())>=15*1000) //this needs to be some sort of timer.
  {
    for (int i = 0; i < 4; i++)
    {
      int reading = analogRead(pinHolding[i]);
      if (reading - cellThresholds[i] > LIT_THRESHOLD)
      {
        colorSequence.push(i + 1);
        start = true;
        while (reading - cellThresholds[i] > LIT_THRESHOLD )
        {
          reading = analogRead(pinHolding[i]);
        }
      }
    }

    if ((colorSequence.count() == (oldCounter+1)) && start)
    {
      oldCounter = colorSequence.count();
      Play(&colorSequence);
      start = false;
    }
  }

  _support.Arm(200,true); //return arm to native position
  return true;

}

bool Challenge::Card()
{


  _support.Arm(200,false); 
  //really, this is all there is to the challenge.......


  _support.Arm(200,true);
  //return true if the system didn't encounter any issues.
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
  switch (servoNum)
  {

  case 0:
    {
      servoCenter.write(PRESS_ANGLE);
      servoCenter.write(REST_ANGLE);
      break;
    }
  case 1:
    {
      servoRed.write(PRESS_ANGLE);
      servoRed.write(REST_ANGLE);
      break;
    }
  case 2:
    {
      servoBlue.write(PRESS_ANGLE);
      servoBlue.write(REST_ANGLE);
      break;
    }
  case 3:
    {
      servoYellow.write(PRESS_ANGLE);
      servoYellow.write(REST_ANGLE);
      break;
    }
  case 4:
    {
      servoGreen.write(PRESS_ANGLE);
      servoGreen.write(REST_ANGLE);
      break;
    }

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



