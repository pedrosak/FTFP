#include <Adafruit_MotorShield.h>
#include "ObjectDetect.h"
#include <NewPing.h>
#include <QueueArray.h>
#include <Average.h>
#include <Servo.h>
#include <Wire.h>
#include <QTRSensors.h>                        //sensor array Polulo library
#define MAX_DISTANCE 200
#define ENC_PER_INCH 0.00806452 //how many inches are in one turn of the encoder  
#define NUMBER_OF_SENSORS 8                    //Number of Sensors being used
#define TIMEOUT           2500                 //2500 microseconds for sensor output to go low
#define EMITTER_PIN       30                    //LEDON pin. Always one, turn off to save power

int echo = 7;
int trg = 8;
bool started = false;
unsigned int sensorValues[NUMBER_OF_SENSORS];

NewPing sonar(trg, echo, MAX_DISTANCE);
Adafruit_MotorShield Etch = Adafruit_MotorShield(0x60);
Adafruit_MotorShield Rubiks = Adafruit_MotorShield(0x61);
Adafruit_MotorShield Move = Adafruit_MotorShield(0x62);
QTRSensorsRC sensors((unsigned char[]) {22, 23, 24, 25, 26, 27,28,29}, NUMBER_OF_SENSORS, TIMEOUT, EMITTER_PIN);
Adafruit_PWMServoDriver servoShield = Adafruit_PWMServoDriver();
const int etchSteps = 48; //configure based upon steppers used
const int PWMFreq = 60; //Micro Servos operate at 60 Hz (Checked by Kurt)
int obj = 0;
/*
READ ME BEFORE PLUGGING THINGS IN!
 
 The motor shield for arm/rubik's should be connected as follows:
 
 1 -> R
 2 -> G
 3 -> Y
 4 -> B
 
 The motor shield for the etch should be connected as follows:
 
 1 -> Brown
 2 -> Black
 3 -> Yellow
 4 -> Orange
 
 Please pay attention to what motor shield is controlling what motors. If possible, we'd like to have
 0x61 be the arm and 0x60 be the etch. 0x62 will be the movement shield.
 
 Please note the pin location and what encoder it applies to in the encoderPins array
 
 */
Adafruit_StepperMotor *left = Etch.getStepper(etchSteps, 1); // motor port #1 (M1 & M2), stepper that controls left knob on Etch-a-Sketch
Adafruit_StepperMotor *right = Etch.getStepper(etchSteps, 2); // motor port #2 (M3 & M4) stepper that controls right knob on Etch-a-Sketch
Adafruit_StepperMotor *rubiks = Rubiks.getStepper(200, 1); // motor port #1 (M1 & M2) stepper that controls Rubiks
Adafruit_StepperMotor *arm = Rubiks.getStepper(200, 2); // motor port #2 (M3 & M4) stepper that controls arm
Adafruit_DCMotor *leftMotor = Move.getMotor(1); // motor port #1 (M1) DC motor that controls left wheel
Adafruit_DCMotor *backMotor = Move.getMotor(2); // motor port #2 (M2) DC motor that controls back wheel
Adafruit_DCMotor *rightMotor = Move.getMotor(3); //motor port #3 (M3) DC motor that controls right wheel

/*

 Motor|Encoder A|Encoder B
 ---------------------------
 1   |   48    |   49
 --------------------------- 
 2   |   50    |   51
 --------------------------- 
 3   |   52    |   53
 
 */
int encoderPins[] = {48,49,50,51,52,53};

int maxMinValues[] = {230,310,230,310,230,310,370,480,100,600};

Support support(arm, leftMotor, backMotor, rightMotor, encoderPins,&sensors,sensorValues); 
Challenge Cha(&support, &servoShield, maxMinValues);
ObjectDetect ObjDet(&support);

void setup() {

  Serial.begin(9600);
  servoShield.begin();
  servoShield.setPWMFreq(PWMFreq);
  Etch.begin();
  Rubiks.begin();
  Move.begin();
  left ->setSpeed(48); //ask Tito why this needs to be 48
  right->setSpeed(48);
  arm->step(100,FORWARD,DOUBLE);
  arm->step(150,BACKWARD,DOUBLE);
  //set all of our encoder pins to input
  for(int i=0; i<(sizeof(encoderPins)/sizeof(int))-1;i++)
  {
    pinMode(encoderPins[i], INPUT); 
  }
  /*
    bool dir = true;
  backMotor->setSpeed(60);
  
  for (int i = 1; i <=400; i++)
  {
    
   if(!(i%50))
   { //multiples of 100

     dir = !dir;
   }

   if(dir)
   {
   backMotor->run(FORWARD);
   }
   else
   {
   backMotor->run(BACKWARD);  
   }
   sensors.calibrate();                        //Reads all sensors 10 times for the TIMEOUT time (if TIMEOUT = 2500 microseconds then 25 ms per call)
  }

  backMotor->run(RELEASE);
*/
}

void loop()
{

  Cha.Etch(left, right, etchSteps);
  
  /*
  if(!started)
  {
    support.StartUp();
    started = true;
  }

  support.Follow();
  //if we find a challenge zone
  ObjDet.Approach(sonar);
  Serial.write('C');
  obj = ObjDet.IdentifyAndAlign();
  ObjDet.WhatObj(obj);

  switch (obj)
  {
  case 1:
    {
      support.Shuffle((int)(-4/ENC_PER_INCH));
      support.BackForward((int)(5.5/ENC_PER_INCH));
      Cha.Etch(left, right, etchSteps);
      support.BackForward((int)(-5.5/ENC_PER_INCH));
      delay(100);
      support.Shuffle((int)(4/ENC_PER_INCH));
      break;
    }
  case 2:
    {
      support.Shuffle((int)(4/ENC_PER_INCH));
      support.BackForward((int)(6/ENC_PER_INCH));
      Cha.Rubiks(rubiks);
      support.BackForward((int)(-6/ENC_PER_INCH));
      delay(500);
      support.Shuffle((int)(-4/ENC_PER_INCH));
      break;
    }
  case 3:
    {
      support.Shuffle((int)(-4/ENC_PER_INCH));
      support.BackForward((int)(7/ENC_PER_INCH));
      Cha.Simon();
      support.BackForward((int)(-7/ENC_PER_INCH));
      delay(100);
      support.Shuffle((int)(4/ENC_PER_INCH));
      break;
    }
  }
*/
}
















