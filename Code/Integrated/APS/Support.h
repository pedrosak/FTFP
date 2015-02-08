#ifndef Support_h
#define Support_h
#endif // Support_h

//this class is intended to be used for support functions (i.e. moving the arm, line follow)
//functions that have no home otherwise.

class Support
{
public:
   Support();
   bool Arm(int steps, bool up);
   void Follow();
   bool StartUp();
   bool Finish();
   void Creep();
   void Shuffle(float dist);
private:
  //we'll want any information relating to pins to be private. The idea is that once its set, we won't touch it
  //we'll create the objects relating to the motor shields here.
  //_ArmStepper;
};
