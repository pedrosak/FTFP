#include "Challenge.h"

Challenge::Challenge()
{
  
  
}


bool Challenge::Rubiks()
{
  
 _support.Arm(200,false); //just place holders. -lower arm to cube
 //complete the challenge
 _support.Arm(200,true); //place holders - return arm to native position
 
//return true if the system didn't encounter any issues
  
}

bool Challenge::Etch()
{
  
  _support.Arm(200,false); //lower the arm to etch
  //complete the challenge
  _support.Arm(200,true); //return arm to native position
  
  //return true if the system didn't encounter any issues
  
}


bool Challenge::Simon()
{
 
   _support.Arm(200,false);
//complete the challenge. Its possible that the arm might need to be raised and lowered here, but no biggie. 
  _support.Arm(200,true);
  
  //return true if the system didn't encounter any issues
  
}

bool Challenge::Card()
{
  
   _support.Arm(200,false); 
   //really, this is all there is to the challenge.......
   _support.Arm(200,true);
   //return true if the system didn't encounter any issues.
}
