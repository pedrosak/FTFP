#include <Adafruit_MotorShield.h>
#include <Servo.h> 
#include <Stepper.h>
#include <Wire.h>
#include <QueueArray.h>
#include <Average.h>


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

int counter = 0;


Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Stepper motors
Adafruit_StepperMotor *rotation = AFMS.getStepper(200, 1); // motor port #1 (M1 & M2)
Adafruit_StepperMotor *z = AFMS.getStepper(200, 2); // motor port #2 (M3 & M4)

void setup() {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 

  AFMS.begin();

  // Stepper Motors
  rotation->setSpeed(200);  // 200 rpm 
  z->setSpeed(200); 
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

  for (int i = 0; i < 4; i++) { 
    photocellVals[i] = analogRead(pinHolding[i]);
  } 

  currentMax = 0;
  maxPin = 0;

  //determine what pin is the highest
  for (int i = 0; i < 4; i++) {
    if (photocellVals[i] > currentMax) {
      currentMax = photocellVals[i];
      maxPin = i;
    } 
  }

  //if we're greater than some threshold
  if (currentMax > cellThresholds[maxPin]) {
    colorSequence.push(maxPin+1);
    start = true;
    counter = 0;
  }
  //otherwise we need to increase our timer (counter)
  else if (currentMax < cellThresholds[maxPin]) {
    counter++;
  }

  if ((counter > TIMEOUT) && (start == true)) { 
    Play(colorSequence);
  }
}

// Determine next stop
void Play(QueueArray <int> colorSequence) {

  while(!colorSequence.isEmpty())
  {
    actuateServo(colorSequence.pop());
  }
  counter = 0;
  start = false;
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

      break; 
    }
  case 1:
    {

      break; 
    }
  case 2:
    {

      break; 
    }
  case 3:
    {

      break; 
    }
  case 4:
    {

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

void pressButton() {
  // Move claw down
  z->step(50, BACKWARD, DOUBLE);  // Down //need to change these values for how far it moves down


  // Move claw up
  z->step(50, FORWARD, DOUBLE); // Up //need to change the values for the new system
}
