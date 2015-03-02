#include <Adafruit_MotorShield.h>
#include <Servo.h> 
#include <Stepper.h>
#include <Wire.h>
#include <QueueArray.h>
#include <Average.h>
#include <Servo.h>


int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellPin1 = 1; 
int photocellPin2 = 2;
int photocellPin3 = 3;

int pinHolding[] = {
  photocellPin, photocellPin1, photocellPin2, photocellPin3
};

int cellThresholds[4];

QueueArray <int> colorSequence;
void Play(QueueArray <int> colorSequence);

int photocellVals[4]; //state of each of the photocells
int currentMax;
int maxPin;
boolean start = false;
boolean gameStarted = false;
const int TIMEOUT = 1000; //timeout for an entire simon seqence
const int PRESS_ANGLE = 50; //angle at which servo will actuate to press button
const int REST_ANGLE = 100; //angle at which servo will rest
Servo servoCenter;
Servo servoRed;
Servo servoBlue;
Servo servoYellow;
Servo servoGreen;
char buffer[256];

int counter = 0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Stepper motors
Adafruit_StepperMotor *rotation = AFMS.getStepper(200, 1); // motor port #1 (M1 & M2)
Adafruit_StepperMotor *z = AFMS.getStepper(200, 2); // motor port #2 (M3 & M4)

void setup() 
{
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 

  AFMS.begin();

  // Stepper Motors
  rotation->setSpeed(200);  // 200 rpm 
  z->setSpeed(200); 

  //Attach servos to pins (need to figure out what pins. 10 is just an example)
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

}

void loop() {

  if(!gameStarted)
  {
    startGame();
    gameStarted = true;
  }

  /*
  read the pins to get their current light values
   reads from each photocell. Numbering convention:
   red - 0
   blue - 1
   yellow - 2
   green - 3  
   */

  //realistically, we can do all the logic here. If the reading - calibration is greater than some number, we know its high.

  for (int i = 0; i < 4; i++) 
  { 
    //photocellVals[i] = analogRead(pinHolding[i]);
    if(analogRead(pinHolding[i])-cellThresholds[i]>50 /*some value*/)
    {
      colorSequence.push(i+1);
      start = true;
      counter = 0;
    }
    else
    {
      counter++;
    }
  } 

  /*
  currentMax = 0;
   maxPin = 0;
   
   //determine what pin is the highest
   for (int i = 0; i < 4; i++) 
   {
   if (photocellVals[i] > currentMax) 
   {
   currentMax = photcellVals[i];
   maxPin = i;
   } 
   }
   
   //if we're greater than some threshold
   if (currentMax > cellThresholds[maxPin]) 
   {
   colorSequence.push(maxPin+1);
   start = true;
   counter = 0;
   }
   //otherwise we need to increase our timer (counter)
   else (currentMax < cellThresholds[maxPin]) 
   {
   counter++;
   }
   */
  if ((counter > TIMEOUT) && (start == true)) 
  { 
    Play(colorSequence);
    counter = 0;
    start = false;
  }
}

// Determine next stop
void Play(QueueArray <int> colorSequence) 
{

  Serial.print("Color sequence length:");
  Serial.println(colorSequence.count());
  while(!colorSequence.isEmpty())
  {
    actuateServo(colorSequence.pop());
  }

}

void actuateServo(int servoNum)
{

  /*
  use this function to actuate the servo. 
   servo numbering scheme:
   center - 0
   red - 1
   blue - 2
   yellow - 3
   green - 4
   */

  switch(servoNum)
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

void startGame()
{
  //we need to read all the sensors about 100 times. Get mode. This will calibrate each sensor for its own lighting conditions

  for(int i = 0; i<4;i++)
  {
    Average<int> ave(100);
    for(int j = 0; j<100;j++)
    {

      ave.push(analogRead(pinHolding[i]));
    }
    cellThresholds[i] = ave.mode();
  }

  actuateServo(0);
}


