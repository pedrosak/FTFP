#include <Adafruit_MotorShield.h>
#include "ObjectDetect.h"
#include <NewPing.h>
#include <Wire.h>
#include <QueueArray.h>
#include <Average.h>
#include <Servo.h>
#define MAX_DISTANCE 200
#define rubixStrafeFromCenter 3.25


/*
    ObjectDetection 
 
 This module will wait for a serial communication from the Pi and turn on
 a corresponding LED.
 
 */


//time it takes to make the turn needs to be changed
//testing is need to map everything at the speed we plan on running it at


int echo=23;
int trg=22;
bool started = false;

NewPing sonar(trg,echo,MAX_DISTANCE);
ObjectDetect ObjDet(22,23);
Challenge Cha;
Support support; //this port is hard coded to 61 in code


 Adafruit_StepperMotor *left;
   Adafruit_StepperMotor *right;
     Adafruit_StepperMotor *rubiks;
       


     Adafruit_MotorShield _Etch = Adafruit_MotorShield(0x60);
   Adafruit_MotorShield _Rubiks = Adafruit_MotorShield(0x61);

void setup(){

  Serial.begin(9600);

  

_Etch.begin();
_Rubiks.begin();

  
  left = _Etch.getStepper(48, 1); // motor port #1 (M1 & M2), stepper that controls left knob on Etch-a-Sketch
 right = _Etch.getStepper(48, 2); // motor port #2 (M3 & M4) stepper that controls right knob on Etch-a-Sketch
 rubiks = _Rubiks.getStepper(200,1); // motor port #1 (M1 & M2) stepper that controls Rubiks

}

void loop()
{
  /*
  if(!started)
  {
    support.StartUp(); 
    started = true;
  }
  */
  /*
  //if we find a challenge zone
  support.Follow();
  //ObjDet.Approach(sonar);
  Serial.write('C');
  digitalWrite(trg,HIGH);
  delay(7000);
  digitalWrite(trg,LOW);
  int obj = ObjDet.IdentifyAndAlign();
  ObjDet.WhatObj(obj);
  */
  for (int obj=1;obj<4;obj++)
  {
  switch (obj)
  {
  case 1:
    {
      Serial.println("Playing Etch");
      //Serial.write('E');
      Cha.Etch(left,right);
      break;
    }
  case 2:
    {
      Serial.println("Playing Rubiks");
      //Serial.write('R');
      Cha.Rubiks(rubiks);
    }
  case 3:
    {
      Serial.println("Playing Simon");
      //Serial.write('S');
      Cha.Simon();
      break;
    }
      Serial.write('C');
  }
  }


}














