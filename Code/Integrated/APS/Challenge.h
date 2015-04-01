#ifndef Challenge_h
#define Challenge_h
#endif // ObjectDetect_h
#include "Support.h"
#include <QueueArray.h>
#include <Average.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>



class Challenge
{
  public:
    Challenge(Support *support, Adafruit_PWMServoDriver *servoShield, int maxMinValues[]);
    bool Rubiks(Adafruit_StepperMotor *rubiks);
    bool Etch(Adafruit_StepperMotor *left, Adafruit_StepperMotor *right, int steps);
    bool Simon();
    bool Card();
  private:
    Support *_support; //pointer to support object. Will be set in constructor
    Adafruit_PWMServoDriver *_servoShield;
    //begin methods for Simon
    void Play(QueueArray <int> *colorSequence);
    void actuateServo(int servoNum);
    void startSimon(int pinHolding[], int length);
    void initializeServo();
    //end methods for Simon

    //begin variables for Simon
    int cellThresholds[4];
    int *pointerToMaxMinValues;
    
    QueueArray <int> colorSequence;

    int photocellVals[4]; //state of each of the photocells
    int LIT_THRESHOLD;

    int photocellPin; // the cell and 10K pulldown are connected to a0
    int photocellPin1;
    int photocellPin2;
    int photocellPin3;
    
    int *_maxMinValues;
    //end variables for Simon

};
