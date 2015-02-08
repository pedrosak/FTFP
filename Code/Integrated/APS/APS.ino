#include "ObjectDetect.h"
#include <NewPing.h>
#include <AccelStepper.h>
#include <Wire.h>
#define MAX_DISTANCE 200
#define rubixStrafeFromCenter 3.25


/*
    ObjectDetection 
 
 This module will wait for a serial communication from the Pi and turn on
 a corresponding LED.
 
 */


//time it takes to make the turn needs to be changed
//testing is need to map everything at the speed we plan on running it at


int trg=23;
int echo=22;
bool started = false;

NewPing sonar(trg,echo,MAX_DISTANCE);
ObjectDetect ObjDet(22,23);
Challenge Cha;
Support support;
void setup(){

  Serial.begin(9600);

}

void loop()
{
  if(!started)
  {
    support.StartUp(); 
  }
  //if we find a challenge zone
  support.Follow();
  ObjDet.Approach(sonar);
  Serial.write('C');
  int obj = ObjDet.IdentifyAndAlign();
  ObjDet.WhatObj(obj);
  switch (obj)
  {
  case 1:
    {
      Serial.write('E');
      Cha.Etch();
      break;
    }
  case 2:
    {
      Serial.write('R');
      Cha.Rubiks();
      break;
    }
  case 3:
    {
      Serial.write('S');
      Cha.Simon();
      break;
    }
  }



}
















