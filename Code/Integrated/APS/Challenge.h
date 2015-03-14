#ifndef Challenge_h
#define Challenge_h
#endif // ObjectDetect_h
#include "Support.h"
#include <QueueArray.h>
#include <Servo.h>
#include <Average.h>
#include <Adafruit_MotorShield.h>

class Challenge
{
public:
   Challenge();
   bool Rubiks(   Adafruit_StepperMotor *rubiks);
   bool Etch(   Adafruit_StepperMotor *left,    Adafruit_StepperMotor *right);
   bool Simon();
   bool Card();
private:
   Support _support;
   //any shield relating to the arm needs to be in here
   
   //begin methods for Simon
   void Play(QueueArray <int> *colorSequence);
   void actuateServo(int servoNum);
   void startSimon(int pinHolding[], int length);
   //end methods for Simon
   
   //begin variables for Simon
   int cellThresholds[4];

   QueueArray <int> colorSequence;

   int photocellVals[4]; //state of each of the photocells
   int LIT_THRESHOLD;
   
   int photocellPin; // the cell and 10K pulldown are connected to a0
   int photocellPin1;
   int photocellPin2;
   int photocellPin3;
   
   Servo servoCenter;
   Servo servoRed;
   Servo servoBlue;
   Servo servoYellow;
   Servo servoGreen;
    
   int PRESS_ANGLE;
   int REST_ANGLE;
  //end variables for Simon
  
  /*
   //Etch a Sketch
   Adafruit_MotorShield _Etch;
   Adafruit_MotorShield _Rubiks;
   Adafruit_StepperMotor *left;
   Adafruit_StepperMotor *right;
   Adafruit_StepperMotor *rubiks;
   */
   
};
