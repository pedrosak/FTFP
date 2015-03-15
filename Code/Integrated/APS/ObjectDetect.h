#ifndef ObjectDetect_h
#define ObjectDetect_h
#endif
#include "Challenge.h"
#include <NewPing.h>

class ObjectDetect
{
public:
  ObjectDetect(int trigPin, int echoPin, Support *support);
  void Commence(NewPing sonar);
  bool Approach(NewPing sonar);
  void WhatObj(int incomingByte);
  int IdentifyAndAlign();
private:
  int _trigPin;
  int _echoPin;
  int _spead;
  int _speedpinA;
  int _pinI1;
  int _pinI2;
  int LED;
  void forward();
  void backward();
  Support *_support;
  

};

