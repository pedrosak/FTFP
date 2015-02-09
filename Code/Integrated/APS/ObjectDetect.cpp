#include "ObjectDetect.h"
#include <NewPing.h>




ObjectDetect::ObjectDetect(int trigPin, int echoPin)
{
  _trigPin=trigPin;
  _echoPin=echoPin;
  _spead = 255;
  _speedpinA = 9;
  _pinI1 = 8;
  _pinI2 = 11;
  pinMode(_pinI1,OUTPUT);
  pinMode(_pinI2,OUTPUT);
  pinMode(_speedpinA,OUTPUT);

}

//called to approach the object. Returns control one it is there. 
bool ObjectDetect::Approach(NewPing sonar)
{
  float uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  while(((float)(uS / US_ROUNDTRIP_CM) >= 4.1 && (float)(uS / US_ROUNDTRIP_CM) <= 4.3))
  {
    delay(50);
    _support.Creep();
  }

  return true;
}


int ObjectDetect::IdentifyAndAlign()
{
  while(true)
  {
    while (Serial.available() > 0) //blocking serial call
    {
      int incomingByte = Serial.read();
      if (incomingByte == 'X')
      {
        //digitalWrite(LED, HIGH);
        float dist = Serial.parseFloat();
        _support.Shuffle(dist);
        Serial.write('M');
        //digitalWrite(LED, LOW);
      }
      else if (incomingByte > 48 && incomingByte < 52)
      {
        return incomingByte-48;
      }
    }
  }
}

//used for handshaking with Pi. Just lets it know we're alright
void ObjectDetect::WhatObj(int incomingByte)
{
  switch (incomingByte)
  {
  case 1:
    {
      Serial.write('E');
      break;
    }
  case 2:
    {
      Serial.write('R');
      break;
    }
  case 3:
    {
      Serial.write('S');
      break;
    }
  }
}

void ObjectDetect::forward()
{
  analogWrite(_speedpinA, _spead);//input a simulation value to set the speed
  digitalWrite(_pinI2, LOW);//turn DC Motor A move anticlockwise
  digitalWrite(_pinI1, HIGH);
}
void ObjectDetect::backward()//
{
  analogWrite(_speedpinA, _spead);//input a simulation value to set the speed
  digitalWrite(_pinI2, HIGH);//turn DC Motor A move clockwise
  digitalWrite(_pinI1, LOW);
}



