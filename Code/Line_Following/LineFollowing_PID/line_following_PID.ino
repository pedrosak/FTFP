//Libraries to include
#include <QTRSensors.h>                        //Line following sensor Library.
#include <Wire.h>                              //Arduino wire libraryl.
#include <Adafruit_MotorShield.h>              //Adafruit motoshield library.
#include "utility/Adafruit_PWMServoDriver.h"   //Required for motorshield use.
#include <PID_v1.h>                            //PID library (www.playground.arduino.cc/Code/PIDLibrary)

//Define
#define NUMBER_OF_SENSORS 8                    //Sets the number of sensors.
#define TIMEOUT           2500                 //Timeout for sensor output to go low
#define EMITTER_PIN       2                    //Led on pin. Always on.

//Motorshield object
Adafruit_MotorShield motorShield = Adafruit_MotorShield();

//Line following sensors
QTRSensorsRC sensors((unsigned char[]) {3,4,5,6,7,8,9,10}, NUMBER_OF_SENSORS, TIMEOUT, EMITTER_PIN);

//Motor ports on Adafruit shield
Adafruit_DCMotor *leftMotor = motorShield.getMotor(1);
Adafruit_DCMotor *rightMotor = motorShield.getMotor(2);

//Array holding line following sensor values
unsigned int sensorValues[NUMBER_OR_SENSORS];

//PID Variables
double setPoint;
double input;
double output;

//PID
//kp,ki,kd
PID lineFollowingPID(&input, &output, &setPoint,10,1,100, DIRECT);

void setup()
{

}

void loop()
{
  
}
