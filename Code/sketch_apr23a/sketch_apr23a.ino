#include <QTRSensors.h>                        //sensor array Polulo library
#include <Wire.h>
#include <Adafruit_MotorShield.h>              //Adafruit motoshield library
#include "utility/Adafruit_PWMServoDriver.h"   //Required for motorshield use
#include <Encoder.h>
#define ENC_PER_INCH 0.00806452 //how many inches are in one turn of the encoder 
//Definitions
#define NUMBER_OF_SENSORS 8                    //Number of Sensors being used
#define TIMEOUT           2500                 //2500 microseconds for sensor output to go low
#define EMITTER_PIN       30                    //LEDON pin. Always one, turn off to save power


//Create motoshield object
Adafruit_MotorShield motorShield = Adafruit_MotorShield(0x62);

//Sensor pins input.
//NEED TO CHANGE SENSOR PINS
//NEED TO CHANGE FUNCTION VALUE FROM SEEING BLACK LINE TO SEEING WHITE LINE
QTRSensorsRC sensors((unsigned char[]) {
  22, 23, 24, 25, 26, 27, 28, 29
}, NUMBER_OF_SENSORS, TIMEOUT, EMITTER_PIN);


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

int encoderPins[] = {48, 49, 50, 51, 52, 53};

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

  for (int i = 1; i <= 400; i++)
  {

    if (!(i % 30))
    { //multiples of 100

      dir = !dir;
    }

    if (dir)
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

void loop() {
  // put your main code here, to run repeatedly:
  BackForward((int)(21.5 / ENC_PER_INCH));
  //turn right

  //straight
  BackForward((int)(7.5 / ENC_PER_INCH));

  //turn left

  //straight
  BackForward((int)(23 / ENC_PER_INCH));

  //turn right

  //straight
  BackForward((int)(6 / ENC_PER_INCH));

  //challenge

  //turn around

  //straight
  BackForward((int)(6 / ENC_PER_INCH));
  //turn right

  //straight
  BackForward((int)(10 / ENC_PER_INCH));
  //challenge

  //stop


}

void BackForward(int dist) //move the system forward or backward
{
  //local variable to keep track of how far the encoder has moved
  int encoderPos = 0;
  int encoderPinALast = LOW;
  int n = LOW;
  int encoderPinA;
  int encoderPinB;

  unsigned int position;
  int lastOutput = 0;
  int output = 0;
  int error = 0;
  int pidOutput = 0;
  int lastError = 0;

  if (dist > 0) //forward
  {
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
    encoderPinA = encoderPins[0];
    encoderPinB = encoderPins[1];
  }
  else //backward
  {
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    encoderPinA = encoderPins[4];
    encoderPinB = encoderPins[5];
  }

  leftMotor->setSpeed(100);
  rightMotor->setSpeed(100);

  //while our encoder position is less than our distance we need to move
  while (abs((float)encoderPos) < abs(dist))
  {
    n = digitalRead(encoderPinA);
    if ((encoderPinALast == LOW) && (n == HIGH))
    {
      if (digitalRead(encoderPinB) == LOW)
      {
        encoderPos--;
      }
      else
      {
        encoderPos++;
      }
    }
    encoderPinALast = n;

    position = sensors.readLine(sensorValues);
    error = position - 3360;
    pidOutput = ((0.1) * error) + (0.8 * (error - lastError));
    output = pidOutput + output;
    lastError = error;

    Move(output);


  }
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  return;
}

void Move(int output)
{
  leftMotor->setSpeed(5 + abs(output));
  rightMotor->setSpeed(5 - abs(output));
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}

void turnAround()
{
int encoderPos = 0;
  int encoderPinALast = LOW;
  int n = LOW;
  int encoderPinA = encoderPins[4];
  int encoderPinB = encoderPins[5];
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
  leftMotor->setSpeed(60);
  rightMotor->setSpeed(120);

  while (abs((float)encoderPos) < abs(3000))
  {
    n = digitalRead(encoderPinA);
    if ((encoderPinALast == LOW) && (n == HIGH))
    {
      if (digitalRead(encoderPinB) == LOW)
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
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  return;



}

void turnRight()
{
  int encoderPos = 0;
  int encoderPinALast = LOW;
  int n = LOW;
  int encoderPinA = encoderPins[4];
  int encoderPinB = encoderPins[5];

  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
  leftMotor->setSpeed(60);
  rightMotor->setSpeed(120);

  while (abs((float)encoderPos) < abs(1500))
  {
    n = digitalRead(encoderPinA);
    if ((encoderPinALast == LOW) && (n == HIGH))
    {
      if (digitalRead(encoderPinB) == LOW)
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
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  return;



}

void turnLeft()
{

  int encoderPos = 0;
  int encoderPinALast = LOW;
  int n = LOW;
  int encoderPinA = encoderPins[0];
  int encoderPinB = encoderPins[1];

  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);
  leftMotor->setSpeed(120);
  rightMotor->setSpeed(60);
  while (abs((float)encoderPos) < abs(1500))
  {
    n = digitalRead(encoderPinA);
    if ((encoderPinALast == LOW) && (n == HIGH))
    {
      if (digitalRead(encoderPinB) == LOW)
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
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  return;

}
