#ifndef ObjectDetect_h
#define ObjectDetect_h
#endif
#include <NewPing.h>

class ObjectDetect
{
public:
  ObjectDetect(int trigPin, int echoPin);
  void Commence(NewPing sonar);
  void reset();
private:
  int _trigPin;
  int _echoPin;
  bool completed;
  bool inRange;
  int _spead;
  int _speedpinA;
  int _pinI1;
  int _pinI2;
  void whatObj(int incomingByte);
  void forward();
  void backward();
  void shuffle();
  

};

