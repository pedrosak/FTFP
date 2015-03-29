#ifndef ObjectDetect_h
#define ObjectDetect_h
#endif
#include "Challenge.h"
#include <NewPing.h>

class ObjectDetect
{
public:
  ObjectDetect(Support *support);
  void Commence(NewPing sonar);
  bool Approach(NewPing sonar);
  void WhatObj(int incomingByte);
  int IdentifyAndAlign();
private:
  Support *_support; //pointer to support object. Will be set in constructor
  int strToInt(char AStr[], byte ALen); //converts incoming serial data to integer
};

