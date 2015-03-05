#include <Adafruit_MotorShield.h>
#include "ObjectDetect.h"
#include <NewPing.h>
#include <AccelStepper.h>
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
Challenge Cha(0x60);
Support support; //this port is hard coded to 61 in code
void setup(){

  Serial.begin(9600);

}

void loop()
{
  if(!started)
  {
    support.StartUp(); 
    started = true;
  }
  //if we find a challenge zone
  support.Follow();
  //ObjDet.Approach(sonar);
  Serial.write('C');
  digitalWrite(trg,HIGH);
  delay(7000);
  digitalWrite(trg,LOW);
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
      digitalWrite(echo,HIGH);
      delay(1000);
      digitalWrite(echo,LOW);
      break;
    }
  case 3:
    {
      Serial.write('S');
      Cha.Simon();
      break;
    }
      Serial.write('C');
  }



}
















