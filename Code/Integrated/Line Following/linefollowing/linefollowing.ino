//Linefollowing code only makes robot go forward.
//Mapping code will make decisions and tell robot to turn.


#include <QTRSensors.h>                        //sensor array Polulo library
#include <Wire.h>
#include <Adafruit_MotorShield.h>              //Adafruit motoshield library
#include "utility/Adafruit_PWMServoDriver.h"   //Required for motorshield use
#include <PID_v1.h>                            //PID library (www.playground.arduino.cc/Code/PIDLibrary)
#include "mapping.h"
#include <Encoder.h>

//Definitions
#define NUMBER_OF_SENSORS 8                    //Number of Sensors being used
#define TIMEOUT           2500                 //2500 microseconds for sensor output to go low
#define EMITTER_PIN       30                    //LEDON pin. Always one, turn off to save power


//Create motoshield object
Adafruit_MotorShield motorShield = Adafruit_MotorShield(0x62);

//Sensor pins input.
//NEED TO CHANGE SENSOR PINS
//NEED TO CHANGE FUNCTION VALUE FROM SEEING BLACK LINE TO SEEING WHITE LINE
QTRSensorsRC sensors((unsigned char[]) {22, 23, 24, 25, 26, 27,28,29}, NUMBER_OF_SENSORS, TIMEOUT, EMITTER_PIN);


//Motor port instance and port assigmnet
//NEED TO CHANGE MOTOR PORTS
Adafruit_DCMotor *leftMotor = motorShield.getMotor(1);
Adafruit_DCMotor *rightMotor = motorShield.getMotor(3);
Adafruit_DCMotor *backMotor = motorShield.getMotor(2);

//Variable array holding sensor values
unsigned int sensorValues[NUMBER_OF_SENSORS];
int lastError = 0;
unsigned int position ;
int lastOutput = 0;
int output = 0;
int error = 0;
int diff = 0;
unsigned int sensorCutoff = 2400;
int flag = 0;
Encoder encoderRight(2,3);

void setup()
{

  position = sensors.readLine(sensorValues, QTR_EMITTERS_ON, true);
  //Calibration of sensors loop
  //This calibration is used to expose the sensors to the most reflective surface and the least
  //reflective surface of the track. This will help with the sensor values and determining where
  //they are in relation to the line.
  motorShield.begin();  
  Serial.begin(9600);

  bool dir = true;
  backMotor->setSpeed(60);
  
  for (int i = 1; i <=400; i++)
  {
    
   if(!(i%30))
   { //multiples of 100

     dir = !dir;
   }

   if(dir)
   {
   backMotor->run(FORWARD);
   }
   else
   {
   backMotor->run(BACKWARD);  
   }
   sensors.calibrate();                        //Reads all sensors 10 times for the TIMEOUT time (if TIMEOUT = 2500 microseconds then 25 ms per call)
  }

  backMotor->run(RELEASE);

}
void loop()
{
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  
  position = sensors.readLine(sensorValues, QTR_EMITTERS_ON, true);
  sensors.read(sensorValues);
   for(int i = 0; i<NUMBER_OF_SENSORS;i++)
  {
      Serial.print(sensorValues[i]);
      Serial.print("\t");  
   }
 
  Serial.println(position);


  if((sensorValues[0] < sensorCutoff && sensorValues[1] < sensorCutoff && sensorValues[2] < sensorCutoff && sensorValues[3] < sensorCutoff) || (sensorValues[7] < sensorCutoff&& sensorValues[6] < sensorCutoff && sensorValues[5] < sensorCutoff && sensorValues[4] < sensorCutoff))
  {

    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    //delay(2000);
    DetermineChoices(rightMotor,leftMotor,&sensors,&encoderRight);
   // return;
  }

  diff = (position - 3360);
  error = diff/10;
  output = ((0.1)*error) + (0*(error-lastError));
  lastError = error;
  
  move(output);

 //  for(int i = 0; i<NUMBER_OF_SENSORS;i++)
 // {
 //     Serial.print(sensorValues[i]);
 //     Serial.print("\t");  
 //  }
 
 // Serial.println(position);

}



//Motor movement fucntion
int move(int pidSPEED)
{
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);

  if(pidSPEED < 0)
  {
    leftMotor->setSpeed(60 - abs(pidSPEED));
    rightMotor->setSpeed(60 + abs(pidSPEED));
  } 
  else if(pidSPEED > 0) 
  {
    leftMotor->setSpeed(60 + abs(pidSPEED));
    rightMotor->setSpeed(60 - abs(pidSPEED));
  }
  else if(pidSPEED == 0)
  {
    leftMotor->setSpeed(50);
    rightMotor->setSpeed(50);
  }
}

bool stopMove()
{
if((sensorValues[0] < 200) && (sensorValues [1] < 200) && (sensorValues[2] < 200) && (sensorValues[3] < 200) && (sensorValues[4] < 200) && (sensorValues [5] < 200) && (sensorValues[6] < 200) && (sensorValues[7] < 200))
{
return true;
}
else
{
  return false;
}

}

void shuffle(int dist) //move system left or right
{
  //local variable to keep track of how far the encoder has moved
  int encoderPos = 0;
  int encoderPinALast = LOW;
  int n = LOW;
  int encoderPinA = 50;
  int encoderPinB = 51;
  
  if(dist>0) //right
  {
    backMotor->run(FORWARD); 
  }
  else //left
  {
    backMotor->run(BACKWARD);
  }

  backMotor->setSpeed(100);
  
  //while our encoder position is less than our distance we need to move
  while(abs((float)encoderPos)<abs(dist))
  {
     n = digitalRead(encoderPinA);
     if((encoderPinALast == LOW) && (n==HIGH))
     {
      if(digitalRead(encoderPinB)==LOW)
      {
       encoderPos--; 
      }
      else
      {
       encoderPos++;
      }
     }
     encoderPinALast = n;
  }
  backMotor->run(RELEASE);
  
  return;
}
