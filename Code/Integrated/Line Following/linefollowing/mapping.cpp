//need to declare motorshields
//need to define constants if there are any
//need to setup qtrrc sensor
//need to setup encoder
#include "mapping.h"
unsigned int line[8]; //current line reading
unsigned int cutoff = 2000; //cutoff point between line and black

//maping variables
int curMap[10][10][2];
bool mappedNodes[10];
int currentNode = 1;
int nextOpenNode = 2;
int frame = 0;
bool mapLeft = false;
bool mapRight = false;
bool mapStraight = false;
//sensor flags for if they turn white
int L0Flag = 0;
int L1Flag = 0;
int L2Flag = 0;
int L3Flag = 0;
int L4Flag = 0;
int L5Flag = 0;
int L6Flag = 0;
int L7Flag = 0;

//================================================================================
//if the robot sees something try to determine if there is a choice available
void DetermineChoices(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, QTRSensorsRC* qtrrc,Encoder *encoderRight){

  //put code to move forward
  RM->setSpeed(50);
  RM->run(FORWARD);

  LM->setSpeed(50);
  LM->run(FORWARD);
Serial.println("In determine choices");
  encoderRight->write(0);
  Serial.println("After encoder right");
  //move forwards 200 steps and constantly read
  while (abs(encoderRight->read()) <1200){
    qtrrc->read(line);
    Serial.println(abs(encoderRight->read()));

    //if sensor 0 sees white raise flag
    if(line[0] < cutoff){
      L0Flag = 1;
    }

    //if sensor 1 sees white raise flag
    if(line[1] < cutoff){
      L1Flag = 1;
    }

    //if sensor 2 sees white raise flag
    if(line[2] < cutoff){
      L2Flag = 1;
    }

    //if sensor 3 sees white raise flag
    if(line[3] < cutoff){
      L3Flag = 1;
    }

    //if sensor 4 sees white raise flag
    if(line[4] < cutoff){
      L4Flag = 1;
    }

    //if sensor 5 sees white raise flag
    if(line[5] < cutoff){
      L5Flag = 1;
    }

    //if sensor 6 sees white raise flag
    if(line[6] < cutoff){
      L6Flag = 1;
    }

    //if sensor 7 sees white raise flag
    if(line[7] < cutoff){
      L7Flag = 1;
    }
    //give encoder value a chance to change
    delay(5);
  }

  //read from line sensor for reading right now
  qtrrc->read(line);

  //if everything lit up, and is now all white stop
  if(L0Flag == 1 && L1Flag == 1 && L2Flag == 1 && L3Flag == 1 && L4Flag == 1 && L5Flag == 1 && L6Flag == 1 && L7Flag == 1 && line[0] < cutoff && line[1] < cutoff && line[7] < cutoff && line[6] < cutoff){
    Choose(RM,LM,encoderRight);
    L0Flag = 0;
    L1Flag = 0;
    L2Flag = 0;
    L3Flag = 0;
    L4Flag = 0;
    L5Flag = 0;
    L6Flag = 0;
    L7Flag = 0;
    return;
  }

  //if everything lit up, and is now white in middle map 4 way intersection
  if(L0Flag == 1 && L1Flag == 1 && L2Flag == 1 && L3Flag == 1 && L4Flag == 1 && L5Flag == 1 && L6Flag == 1 && L7Flag == 1 && line[3] < cutoff && line[4] < cutoff){
    mapRight = true;
    mapLeft = true;
    mapStraight = true;
    mapping();
    Choose(RM,LM,encoderRight);
    L0Flag = 0;
    L1Flag = 0;
    L2Flag = 0;
    L3Flag = 0;
    L4Flag = 0;
    L5Flag = 0;
    L6Flag = 0;
    L7Flag = 0;
    return;
  }

  //if everything lit up, and is all black map left and right
  if(L0Flag == 1 && L1Flag == 1 && L2Flag == 1 && L3Flag == 1 && L4Flag == 1 && L5Flag == 1 && L6Flag == 1 && L7Flag == 1 && line[3] > cutoff && line[4] > cutoff){
    mapRight = true;
    mapLeft = true;
    mapping();
    Choose(RM,LM,encoderRight);
    L0Flag = 0;
    L1Flag = 0;
    L2Flag = 0;
    L3Flag = 0;
    L4Flag = 0;
    L5Flag = 0;
    L6Flag = 0;
    L7Flag = 0;
    return;
  }

  //if right lit up and middle is lit up map straight and right
  if(line[3] < 1000 && line[4] < 1000 && L0Flag == 1 && L1Flag == 1){
    mapRight = true;
    mapStraight = true;
    mapping();
    Choose(RM,LM,encoderRight);
    L0Flag = 0;
    L1Flag = 0;
    L2Flag = 0;
    L3Flag = 0;
    L4Flag = 0;
    L5Flag = 0;
    L6Flag = 0;
    L7Flag = 0;
    return;
  }

  //if left lit up and middle is lit up map left
  if(line[3] < 1000 && line[4] < 1000 && L6Flag == 1 && L7Flag == 1){
    mapLeft = true;
    mapStraight = true;
    mapping();
    Choose(RM,LM,encoderRight);
    L0Flag = 0;
    L1Flag = 0;
    L2Flag = 0;
    L3Flag = 0;
    L4Flag = 0;
    L5Flag = 0;
    L6Flag = 0;
    L7Flag = 0;
    return;
  }

  //if right only lit up turn right
  if(L0Flag == 1 && L1Flag == 1){
    turnRight(RM,LM,encoderRight);
    L0Flag = 0;
    L1Flag = 0;
    L2Flag = 0;
    L3Flag = 0;
    L4Flag = 0;
    L5Flag = 0;
    L6Flag = 0;
    L7Flag = 0;
    return;
  }
  //if left only lit up turn left
  if(L6Flag == 1 && L7Flag == 1){
    turnLeft(RM,LM,encoderRight);
    L0Flag = 0;
    L1Flag = 0;
    L2Flag = 0;
    L3Flag = 0;
    L4Flag = 0;
    L5Flag = 0;
    L6Flag = 0;
    L7Flag = 0;
    return;
  }
}

//=========================================================================
//choose where to go

//frame is where the robots curent frame of reference is
//it is one of the following
//
//				1						0						3						2
//	frame 0: 2		0	frame 1:	1		3	frame 2:	0		2	frame 3:	3		1
//				3						2						1						0
//
//it is assumed that the robot starts at frame 0.
//every left turn the robot takes its current frame and rotates it 90 degrees, IE (frame + 1)%4
//every right turn the robot takes its current frame and rotates it 270 degrees, equivalent to -90 degrees, IE (frame + 3)%4
//every straight choice the robot takes its current frame and keeps it the same, IE (frame + 0)%4
//every back choice the robot takes its current frame and rotates it 180 degrees, IE (frame + 2)%4

//in order to determine which way to go the robot searches through a 2D array where the rows are where the robot is going from, and columns are where its going to.
//it will always have the row value of currentNode because it is always leaving that node, and it looks for any possible node it can go to

//if((frame + 1)%4 == curMap[currentNode][i][0] && curMap[currentNode][i][1] == 0)
//this line means: if the current frame rotated 90 degrees is equal to the node in the 2D array going from the current node to node i, and is checking if that path has
//been used.

//The reason this works is because the choices are stored based on a left is always 1, a right is always 3, and a straight is always 0.
//The reverse of this is also true.

//Lets say you start at frame 0 and you have a left and a straight. Node 0 is the start, you are at node 1, node 2 is to your left, node 3 is straight ahead.
//You take your current frame of 0 and check it against the possibilities left, right, straight, back. this is done by (frame+n)%4 where n is how many 90 degrees
//you turn. At first you will have (frame + 1)%4 giving (0+1)%4 = 1. You look at your map curMap[where you are][where you are going to][0 for direction, 1 for was the path taken]
//You will find that (0+1)%4 is equal to curMap[1][2][0] which is 1, and curMap[1][2][1] is false meaning you haven't taken that edge
//You go left. Your current frame is updated to frame 1. Next you reach a game and turn around. This means you add 2 to your current frame leaving you with
//frame 3. You have effectively turned 90 degrees left 3 times thus you are facing 270 degrees from where you originally were. Now when you go back to the original
//choice your starting position is on the right, the straight away is on your left, and the original left turn is behind you and your current frame is 3. Now you
//check if any other options were available. You will use (frame + 1)%4 which will give you(3+1)%4 = 0. Next you compare this value against the map.
//curMap[1][0][0] is frame 2, 2 != 0, so you look at curMap[1][1][0] which does not exist, since you are at node 1. Then you have curMap[1][2][0] which is frame 1.
//lastly you check curMap[1][3][0] which is frame 0. Since curMap and your current frame + 1 % 4 are both 0 that means you take the original straight away path.
//You do this by going left because you add 1 to the frame to equal the curMap frame.

void Choose(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight){
  for(int i = currentNode; i < 10; i++){
    if(curMap[currentNode][i][0]  != 5){
      //check if left was available
      if((frame + 1)%4 == curMap[currentNode][i][0] && curMap[currentNode][i][1] == 0){
        //turn left

        //turnLeft(RM,LM,encoderRight);
        turnRight(RM,LM,encoderRight);
        frame = (frame + 1)%4;
        curMap[currentNode][i][1] = 1;
        currentNode = i;
        return;
      }

      //check if right was available
      else if((frame + 3)%4 == curMap[currentNode][i][0] && curMap[currentNode][i][1] == 0){
        //turn right

        //turnRight(RM,LM,encoderRight);
        turnLeft(RM,LM,encoderRight);
        frame = (frame + 3)%4;
        curMap[currentNode][i][1] = 1;
        currentNode = i;
        return;
      }

      //check if straight was available
      else if((frame + 0)%4 == curMap[currentNode][i][0] && curMap[currentNode][i][1] == 0){
        //go straight

        //line follow here
        curMap[currentNode][i][1] = 1;
        currentNode = i;
        return;
      }
    }
  }
  //if first for loop is exhausted and no turn / straight is available then turn around
  for(int i = 0; i < currentNode; i++){
    if(curMap[currentNode][i][0] != 5){
      if((frame + 2)%4 == curMap[currentNode][i][0] && curMap[currentNode][i][1] == 0){

        //play your current game
        turnAround(RM,LM,encoderRight);
        frame = (frame + 2)%4;
        curMap[currentNode][i][1] = 1;
        currentNode = i;
        return;
      }
    }
  }
}

//=========================================================================
//creating internal map of course
void mapping(){

  //changing order of assignment alters choice pattern
  //checking left, then right, then straight results in prioritizing
  //left turn, then right turn, then go straight.
  //if left choice is true
  //create edge between current node and next node
  if(mapLeft == true && mappedNodes[currentNode] == false){
    curMap[currentNode][nextOpenNode][0] = (frame + 1)%4;
    curMap[nextOpenNode][currentNode][0] = (frame + 3)%4;
    nextOpenNode++;
  }

  //if right edge is true
  //create edge between current node and next node
  if(mapRight == true && mappedNodes[currentNode] == false){
    curMap[currentNode][nextOpenNode][0] = (frame + 3)%4;
    curMap[nextOpenNode][currentNode][0] = (frame + 1)%4;
    nextOpenNode++;
  }

  //if straight choice is true
  //create edge between current node and next node
  if(mapStraight == true && mappedNodes[currentNode] == false){
    curMap[currentNode][nextOpenNode][0] = (frame + 0)%4;
    curMap[nextOpenNode][currentNode][0] = (frame + 2)%4;
    nextOpenNode++;
  }
  mapStraight = false;
  mapRight = false;
  mapLeft = false;

  mappedNodes[currentNode] = true;
}

//==========================================================================
//setup for mapped nodes
void setupMappedNodes(){
  for(int i = 0; i < 10; i++){
    mappedNodes[i] = false;
  }
}


//===================================================================================================================================================================
//setup map for graph
void setupMap(){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      curMap[i][j][0] = 5;
      curMap[i][j][1] = 0;
    }
  }
  curMap[0][1][0] = 0;
  curMap[1][0][0] = 2;
}

void turnLeft(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight)
{


  LM->run(BACKWARD);
  RM->run(FORWARD);
  LM->setSpeed(120);
  RM->setSpeed(60);

  encoderRight->write(0);
  //move forwards 200 steps and constantly read
  while (abs(encoderRight->read()) <1500){
    delay(1);
  }
}

void turnRight(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight)
{

  LM->run(FORWARD);
  RM->run(BACKWARD);
  LM->setSpeed(60);
  RM->setSpeed(120);

  encoderRight->write(0);
  //move forwards 200 steps and constantly read
  while (abs(encoderRight->read()) <1500){
    delay(1);
  }

}

void turnAround(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight)
{

  LM->run(FORWARD);
  RM->run(BACKWARD);
  LM->setSpeed(60);
  RM->setSpeed(60);
  encoderRight->write(0);
  //move forwards 200 steps and constantly read
  while (abs(encoderRight->read()) <3000){
    delay(1);
  }
}


