void setup() {
  // put your setup code here, to run once:
  bool started = false;
  //array for completed challenges
}

void loop() {
  // put your main code here, to run repeatedly:

}


void Mainfn()
{
  
 if(!started)
{
 monitorStart();
} 
  else if(!challengeArea())
  {

  //some function to check to junctions 
  if(!junctionDetected())
  {
  lineFollow();
  }
  else
   {
    turn(); 
     
   }
    
    
  }
  else
  {
    //must be a challenge
       //switch statement for challenge seen
    switch(areaArrival())
    {
      
      
      
    }
    //call function to turn around
    exitArea();
    
    
  }
  
}

bool monitorStart()
{
  
 //check the status of the start LED
//once the LED goes out, raise the flag to true 
  
}

void lineFollow()
{
 //line following code goes here
//any function associated with correcting will reside here 
  
}

bool junctionDetected()
{
 //check serial line for something from Pi. 
 //if pertains to junction
 //turn
 //else
 //must belong to object detection and we should store it to a temp variable
  
}

void turn()
{
 //function turns robot left or right depending upon input. 
  
}

void shuffle()
{
  //function to shuffle left or right based on input
}

int areaArrival()
{
  //code to creep to challenges
 //code to initialize Pi's camera (if not already on) [this is a design choice. currently the camera is only on at a challenge area]
 //code to align
 //code to move up
 //returns int based on challenge seen
}

void Simon()
{
}
void Etch()
{
}
void rubiks()
{
}
void card()
{
}

void exitArea()
{
  
}


