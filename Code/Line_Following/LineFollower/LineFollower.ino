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
Adafruit_MotorShield motorShield = Adafruit_MotorShield();

//Sensor pins input.
QTRSensorsRC sensors((unsigned char[]) {3, 4, 5, 6, 7, 9}, NUMBER_OF_SENSORS, TIMEOUT, EMITTER_PIN);
//Motor port instance and port assigmnet
Adafruit_DCMotor *leftMotor = motorShield.getMotor(1);
Adafruit_DCMotor *rightMotor = motorShield.getMotor(2);

//Variable array holding sensor values
unsigned int sensorValues[NUMBER_OF_SENSORS];

//PID Variables
double setPoint,
       input,
       output;
//PID instaqnce with parameters
PID lineFollowingPID(&input, &output, &setPoint,1,0,0, DIRECT);

int error;

void setup()
{
  //Calibration of sensors loop
  //This calibration is used to expose the sensors to the most reflective surface and the least
  //reflective surface of the track. This will help with the sensor values and determining where
  //they are in relation to the line.
  delay(500);                                  //Delay of 500 miliseconds
  pinMode(13, OUTPUT);
  
  //Calibration
  digitalWrite(13, HIGH);                      //Sets the arduino board LED to HIGH
  for (int i = 0; i <400; i++)
  {
   sensors.calibrate();                        //Reads all sensors 10 times for the TIMEOUT time (if TIMEOUT = 2500 microseconds then 25 ms per call)
  }
  digitalWrite(13, LOW);                       //Sets arduino borad LED to LOW to signal end of calibration
  //End Calibration
  
  Serial.begin(9600);
  
 ///////////////////////////////////////////////////////////////////////////////
  //Display of sensor calibration minimal value readings
  for (int i = 0; i < NUMBER_OF_SENSORS; i++)
  {
    Serial.print(sensors.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
 
  //Display of sensor calibration maximum value readings
  for (int i = 0; i < NUMBER_OF_SENSORS; i++)
  {
    Serial.print(sensors.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);                                 //delay for 1000 microseconds
/////////////////////////////////////////////////////////////////////////////////

  motorShield.begin();                         //Default frequency of 1.6KHz
  leftMotor->setSpeed(100);                    //Speed of the left motor -- 0 (stopped) - 255 (full speed)
  rightMotor->setSpeed(100);                   //Speed of the left motor -- 0 (stopped) - 255 (full speed)
  goForward();

  //PID
  setPoint = 2500;                             //Sensor posistion when sensor 4 and sensor 3 are on the line.
  lineFollowingPID.SetMode(AUTOMATIC);
  lineFollowingPID.SetOutputLimits(-2500, 2500);
  lineFollowingPID.SetSampleTime(10);
}
void loop()
{
  //Line Position. Values from 0 to 5000
  //If line over sensor 6 alone position value should read 5000
  unsigned int position = sensors.readLine(sensorValues);
  input = position;
  lineFollowingPID.Compute();
  
  if(output == 0){
    goForward();
  } else if (output > 1000){
    turnRight();
  } else if (output < 1000){
    turnLeft();
  }

/////////////////////////////////////////////////////////////////////////////////////////////
  //Print sensor values of 0 to 1000. from most reflective (0) to lest reflective (1000)
    for (unsigned char i = 0; i < NUMBER_OF_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);
  Serial.println(output);
  delay(100);            //Delay of 100 microseconds
/////////////////////////////////////////////////////////////////////////////////////////////
}



//Motor movement fucntions
//Forward
int goForward()
{
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  Serial.println("Forward");
  return 1;
}
//Backward
int goBackwards()
{
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
  Serial.println("Backwards");
  return 1;
}
//Turn Left
int turnLeft()
{
  leftMotor->run(RELEASE);
  rightMotor->run(FORWARD);
  Serial.println("Left");
  return 1;
}
//Turn Right
int turnRight()
{
  leftMotor->run(FORWARD);
  rightMotor->run(RELEASE);
  Serial.println("Right");
  return 1;
}
//Rotate
int rotate()
{
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
  Serial.println("Rotate");
  return 1;
}
