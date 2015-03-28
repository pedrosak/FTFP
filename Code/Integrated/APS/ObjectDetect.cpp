#include "ObjectDetect.h"
#include <NewPing.h>




ObjectDetect::ObjectDetect(Support *support)
{
  _support = support; //pointer to the support object. All modules will use same support object
}

//called to approach the object. Returns control one it is there.
bool ObjectDetect::Approach(NewPing sonar)
{
  float uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //Serial.println((float)(uS / US_ROUNDTRIP_CM));
  while (!(((float)(uS / US_ROUNDTRIP_CM) >= 7.0 && (float)(uS / US_ROUNDTRIP_CM) <= 7.3)))
  {
    delay(50);
    _support->Creep();
    uS = sonar.ping();
    //Serial.println((float)(uS / US_ROUNDTRIP_CM));
  }

  return true;
}


int ObjectDetect::IdentifyAndAlign()
{
  while (true) //we will escape this only once we have a valid byte read
  {
    if (Serial.available() > 0) //blocking serial call
    {
      int incomingByte = Serial.read();
      if (incomingByte == 'X')
      {
          Serial.write('X');
          while(Serial.available()>0);
          int dist = 0;
          bool negative = false;
          char incomingByte;
          while(1)
          {
            incomingByte = Serial.read();
            
            if(incomingByte == '\n') break;
            if(incomingByte == -1) continue;
            if(incomingByte == 45) 
            {
              negative = true;
              continue;
            }
            dist *=10;
            dist=((incomingByte-48)+dist);
            Serial.write('G');
    
          }
          if(negative)
          {
            dist *=-1;
          }
          _support->Shuffle(dist);
          Serial.write('M');

          
        
      }
      else if (incomingByte > 48 && incomingByte < 52) //between one and 4
      {
        return incomingByte - 48; //get rid of ascii encodingascii ch
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
  Serial.write('C');
}




