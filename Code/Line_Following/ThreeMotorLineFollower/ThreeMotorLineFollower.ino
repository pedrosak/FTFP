#include <QTRSensors.h>                        //sensor array Polulo library
#include <Wire.h>
#include <Adafruit_MotorShield.h>              //Adafruit motoshield library
#include "utility/Adafruit_PWMServoDriver.h"   //Required for motorshield use
#include <PID_v1.h>                            //PID library (www.playground.arduino.cc/Code/PIDLibrary)

//Definitions
#define NUMBER_OF_SENSORS 6                    //Number of Sensors being used
#define TIMEOUT           2500                 //2500 microseconds for sensor output to go low
#define EMITTER_PIN       2                    //LEDON pin. Always one, turn off to save power

//Create motoshield object
Adafruit_MotorShield motorShield = Adafruit_MotorShield(0x61);


//Sensor pins input.
QTRSensorsRC sensors((unsigned char[]) {3, 4, 5, 6, 7, 9}, NUMBER_OF_SENSORS, TIMEOUT, EMITTER_PIN);
//Motor port instance and port assigmnet
Adafruit_DCMotor *leftMotor = motorShield.getMotor(2);
Adafruit_DCMotor *rightMotor = motorShield.getMotor(1);
Adafruit_DCMotor *centerMotor = motorShield.getMotor(4);

//Variable array holding sensor values
unsigned int sensorValues[NUMBER_OF_SENSORS];

//PID Variables
double position,
       setPoint,
       input,
       output;
int ratio;

//PID instaqnce with parameters
PID lineFollowingPID(&input, &output, &setPoint,1,10,100, DIRECT);


void setup()
{
  //Calibration
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);                      //Sets the arduino board LED to HIGH
  for (int i = 0; i <200; i++)
  {
   sensors.calibrate();                        //Reads all sensors 10 times for the TIMEOUT time (if TIMEOUT = 2500 microseconds then 25 ms per call)
  }
  digitalWrite(13, LOW);                       //Sets arduino borad LED to LOW to signal end of calibration
  //End Calibration

  Serial.begin(9600);

  
  motorShield.begin();
  //Motor configuration
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  centerMotor->run(RELEASE);

  //PID
  setPoint = 2500;
  lineFollowingPID.SetMode(AUTOMATIC);
  lineFollowingPID.SetOutputLimits(0, 3000);
  lineFollowingPID.SetSampleTime(10);
}





void loop()
{
  //Line Position. Values from 0 to 5000
  //If line over sensor 6 alone position value should read 5000
  position = sensors.readLine(sensorValues);
  input = position;
  lineFollowingPID.Compute();
  move(output);
  
  /////////////////////////////////////////////////////////////////////////////////////////////
  //Print sensor values of 0 to 1000. from most reflective (0) to lest reflective (1000)
    for (unsigned char i = 0; i < NUMBER_OF_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.print(output);
  Serial.print('\t');
  Serial.println(position);

 ////////////////////////////////////////////////////////////////////////////////////////////

//  if(sensorRead() == 0){  
//    move(output);
//  }else if(sensorRead() == 1){
//    leftTurn(output);
//  }else if(sensorRead() == 2){
//    rightTurn(output);
//  }

}





//========================================================================================================================
//========================================================================================================================
//======================================================FUNCTIONS=========================================================
//========================================================================================================================
//========================================================================================================================

//Motor movement fucntion
//FOR THE CENTERMOTOR: FORWARD = RIGHT ------ BACKWARD = LEFT

int move(int output)
{
  ratio = map(output, 0,3000, -50, 50);
  
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    leftMotor->setSpeed(50 + ratio);
    rightMotor->setSpeed(50 - ratio);
    if((50 + ratio) > (50 - ratio)){
     centerMotor->run(FORWARD);
     centerMotor->setSpeed(50 + ratio);
    }else if((50 + ratio) < (50 - ratio)){
    centerMotor->run(BACKWARD);
    centerMotor->setSpeed(50 - ratio);
    } 
    position = sensors.readLine(sensorValues);

  
  while((sensorValues[0] + sensorValues[1] + sensorValues[2]) < 200 && sensorValues[5] > 200) {
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    centerMotor->run(FORWARD);
    leftMotor->setSpeed(50);
    rightMotor->setSpeed(50);
    centerMotor->setSpeed(50);
      position = sensors.readLine(sensorValues);
  }
  
   while((sensorValues[3] + sensorValues[4] + sensorValues[5]) < 200 && sensorValues[0] > 200) {
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
    leftMotor->setSpeed(50);
    rightMotor->setSpeed(50);
    centerMotor->run(BACKWARD);
    centerMotor->setSpeed(50);
      position = sensors.readLine(sensorValues);
  }
  
   if((sensorValues[0] + sensorValues[1] + sensorValues[2] + sensorValues[3] + sensorValues[4] + sensorValues[5]) < 200 && sensorValues[0] > 200) {
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    centerMotor->run(FORWARD);
    centerMotor->setSpeed(50);
    leftMotor->setSpeed(50);
    rightMotor->setSpeed(50);
      position = sensors.readLine(sensorValues);
    
    if((sensorValues[0] + sensorValues[1] + sensorValues[2]) < 200) {
      leftMotor->run(RELEASE);
      rightMotor->run(RELEASE);
      centerMotor->run(RELEASE);      
    }
    
  }
}

////Turn Left
//int leftTurn(int output)
//{
//  ratio = map(output, 0,5000, -50, 50);
//  leftMotor->run(BACKWARD);
//  rightMotor->run(FORWARD);
//  centerMotor->run(BACKWARD);
//  leftMotor->setSpeed(100 + ratio);
//  rightMotor->setSpeed(100 - ratio);
//  centerMotor->setSpeed(50);
//}
////Turn Right
//int rightTurn(int output)
//{
//  ratio = map(output, 0,5000, -50, 50);
//  leftMotor->run(FORWARD);
//  rightMotor->run(BACKWARD);
//  centerMotor->run(FORWARD);
//  leftMotor->setSpeed(100 + ratio);
//  rightMotor->setSpeed(100 - ratio);
//  centerMotor->setSpeed(50);
//}
////rotate ALWAYS TO THE RIGHT
//int rotate(int output)
//{
//  ratio = map(output, 0,5000, -50, 50);
//  leftMotor->run(FORWARD);
//  rightMotor->run(BACKWARD);
//  centerMotor->run(FORWARD);
//  leftMotor->setSpeed(100 + ratio);
//  rightMotor->setSpeed(100 - ratio);
//  centerMotor->setSpeed(50);
//  //ADD ENCODER LOGIC
//}
//
////SENSOR READING
//int sensorRead()
//{
// int leftSensor, rightSensor, allSensor, lineDirection;
// 
// //find average of left, right.
// leftSensor = (sensorValues[0] + sensorValues[1] + sensorValues[2])/3;
// rightSensor = (sensorValues[3] + sensorValues[4] + sensorValues[5])/3;
// 
// //Read logic. If the average of tthe left most sensors is 200 then turn left (1).
// //If average of Right most sensors is less than 200 then turn right (2)
// //Else, go straight (0)
// if((leftSensor < 200) && (rightSensor > 200)){
//   lineDirection = 1;
//   return lineDirection;
// }else if ((rightSensor < 200) && (leftSensor > 200)) {
//   lineDirection = 2;
//   return lineDirection;
// }else {
//   lineDirection = 0;
//   return lineDirection;
// }
//}
