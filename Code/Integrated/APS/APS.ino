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
void setup(){

  Serial.begin(9600);



}

void loop()
{
ObjDet.Commence(sonar);
}















