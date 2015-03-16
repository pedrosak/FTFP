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



Adafruit_MotorShield Etch = Adafruit_MotorShield(0x60);
Adafruit_MotorShield Rubiks = Adafruit_MotorShield(0x61);


Adafruit_StepperMotor *left = Etch.getStepper(48, 1); // motor port #1 (M1 & M2), stepper that controls left knob on Etch-a-Sketch
Adafruit_StepperMotor *right = Etch.getStepper(48, 2); // motor port #2 (M3 & M4) stepper that controls right knob on Etch-a-Sketch
Adafruit_StepperMotor *rubiks = Rubiks.getStepper(200,1); // motor port #1 (M1 & M2) stepper that controls Rubiks
Adafruit_StepperMotor *arm = Rubiks.getStepper(200,2); // motor port #1 (M1 & M2) stepper that controls Rubiks    




Support support(arm); //this port is hard coded to 61 in code
Challenge Cha(&support);
ObjectDetect ObjDet(22,23,&support);

void setup(){

  Serial.begin(9600);

  

Etch.begin();
Rubiks.begin();
left ->setSpeed(48);
right->setSpeed(48);
  
  

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
  case 2:
    {
      Serial.println("Playing Etch");
      //Serial.write('E');
      Cha.Etch(left,right);
      break;
    }
  case 1:
    {
      Serial.println("Playing Rubiks");
      //Serial.write('R');
      Cha.Rubiks(rubiks);
      break;
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














