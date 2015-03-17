#include "ObjectDetect.h"
#include <NewPing.h>




ObjectDetect::ObjectDetect(int trigPin, int echoPin, Support *support)
{
  _support = support; //pointer to the support object. All modules will use same support object
}

//called to approach the object. Returns control one it is there.
bool ObjectDetect::Approach(NewPing sonar)
{
  float uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  while (((float)(uS / US_ROUNDTRIP_CM) >= 4.1 && (float)(uS / US_ROUNDTRIP_CM) <= 4.3))
  {
    delay(50);
    _support->Creep();
  }

  return true;
}


int ObjectDetect::IdentifyAndAlign()
{
  while (true) //we will escape this only once we have a valid byte read
  {
    while (Serial.available() > 0) //blocking serial call
    {
      int incomingByte = Serial.read();
      if (incomingByte == 'X')
      {
        float dist = Serial.parseFloat(); //might want some form of hand shake here to indicate that its okay to send over distance. Will investigate
        _support->Shuffle(dist);
        Serial.write('M');
      }
      else if (incomingByte > 48 && incomingByte < 52) //between one and 4
      {
        return incomingByte - 48; //get rid of ascii encoding
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




