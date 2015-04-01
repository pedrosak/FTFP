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
  Serial.println((float)(uS / US_ROUNDTRIP_CM));
  while (!(((float)(uS / US_ROUNDTRIP_CM) >= 6.2 && (float)(uS / US_ROUNDTRIP_CM) <= 6.4)))
  {
    _support->Creep();
    uS = sonar.ping();
    Serial.println((float)(uS / US_ROUNDTRIP_CM));
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
      int dist;
      byte readLen = 0;
      char buffer[64];
      if (incomingByte == 'X')
      {
        while(!Serial.available());
        readLen = Serial.readBytes(buffer,64);
        dist = strToInt(buffer,readLen);
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

//used to convert incoming serial data to an integer
int ObjectDetect::strToInt(char AStr[], byte ALen)
{
 int Result = 0;
 int c;
 bool negative = false;
 for(int i = 0; i < ALen; i++)
 {
   if(AStr[i] == 45)
   {
     negative = true;
     continue;
   }
   
  c = int(AStr[i] - '0');
  if(c<0 || c >9)
   return -1;
  Result = (Result * 10) +c ;
  
 } 
 
 if(negative)
  return Result*-1; 
 else
  return Result;
  
}


