//Linefollowing code only makes robot go forward.
//Mapping code will make decisions and tell robot to turn.


#include <QTRSensors.h>                        //sensor array Polulo library
#include <Wire.h>
#include <Adafruit_MotorShield.h>              //Adafruit motoshield library
#include "utility/Adafruit_PWMServoDriver.h"   //Required for motorshield use
#include <PID_v1.h>                            //PID library (www.playground.arduino.cc/Code/PIDLibrary)

//Definitions
#define NUMBER_OF_SENSORS 8                    //Number of Sensors being used
#define TIMEOUT           2500                 //2500 microseconds for sensor output to go low
#define EMITTER_PIN       2                    //LEDON pin. Always one, turn off to save power


//Create motoshield object
Adafruit_MotorShield motorShield = Adafruit_MotorShield();

//Sensor pins input.
//NEED TO CHANGE SENSOR PINS
//NEED TO CHANGE FUNCTION VALUE FROM SEEING BLACK LINE TO SEEING WHITE LINE
QTRSensorsRC sensors((unsigned char[]) {3, 4, 5, 6, 7, 9}, NUMBER_OF_SENSORS, TIMEOUT, EMITTER_PIN);


//Motor port instance and port assigmnet
//NEED TO CHANGE MOTOR PORTS
Adafruit_DCMotor *leftMotor = motorShield.getMotor(1);
Adafruit_DCMotor *rightMotor = motorShield.getMotor(2);

//Variable array holding sensor values
unsigned int sensorValues[NUMBER_OF_SENSORS];

//PID Variables
double setPoint,
       input,
       output;
//PID instaqnce with parameters
PID lineFollowingPID(&input, &output, &setPoint,10,1,100, DIRECT);

//NEED TO SETOUTPUT LIMIT FOR PID
//(-255,255) LIMIT


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

  //NEED TO MANUALLY CALIBRATE. 
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

  //delay(1000);                                 //delay for 1000 microseconds
/////////////////////////////////////////////////////////////////////////////////

  motorShield.begin();                         //Default frequency of 1.6KHz
 // leftMotor->setSpeed(50);                    //Speed of the left motor -- 0 (stopped) - 255 (full speed)
 // rightMotor->setSpeed(50);                   //Speed of the left motor -- 0 (stopped) - 255 (full speed)
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  
  //PID
  //SETPOINT NEEDS TO BE ADJUSTED
  setPoint = 2343;                             //Sensor posistion when sensor 4 and sensor 3 are on the line.
  lineFollowingPID.SetMode(AUTOMATIC);
  lineFollowingPID.SetOutputLimits(-900, 900);
  lineFollowingPID.SetSampleTime(10);
}
void loop()
{
  //Line Position. Values from 0 to 7000
  //If line over sensor 6 alone position value should read 5000
  unsigned int position = sensors.readLine(sensorValues, QTR_EMITTERS_ON, true);

  input = position;
  lineFollowingPID.Compute();

  move(output);

//THIS IS NOT NEEDED.
/////////////////////////////////////////////////////////////////////////////////////////////
  //Print sensor values of 0 to 1000. from most reflective (0) to lest reflective (1000)
    for (unsigned char i = 0; i < NUMBER_OF_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);
  //Serial.println(output);
  //delay(100);            //Delay of 100 microseconds
/////////////////////////////////////////////////////////////////////////////////////////////
}



//Motor movement fucntion
int move(int output)
{
  //MAPING AND RATIO NOT NEEDED
  //HERE FOR TESTING.
  int ratio;
  ratio = map(output, -900,900, -50, 50);

  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  leftMotor->setSpeed(abs(output));
  rightMotor->setSpeed(abs(output));
}
