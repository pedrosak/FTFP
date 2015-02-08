#ifndef Challenge_h
#define Challenge_h
#endif // ObjectDetect_h
#include "Support.h"

class Challenge
{
public:
   Challenge();
   bool Rubiks();
   bool Etch();
   bool Simon();
   bool Card();
private:
   Support _support;
   //any shield relating to the arm needs to be in here
};
