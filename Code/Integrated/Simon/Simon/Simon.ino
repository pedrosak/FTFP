#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
#include <Stepper.h>
#include <Wire.h>
#include <QueueArray.h>
#include <Average.h>
#include <Servo.h>

//We might have to address this shield. If so, find out which address
//was given to this shield and input it inside the (). e.x: Adafruit_PWMServoDriver(ADDRESS)
Adafruit_PWMServoDriver servoShield = Adafruit_PWMServoDriver();

int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellPin1 = 1;
int photocellPin2 = 2;
int photocellPin3 = 3;

int pinHolding[] = {
  photocellPin, photocellPin1, photocellPin2, photocellPin3
};

int cellThresholds[4];

QueueArray <int> colorSequence;
void Play(QueueArray <int> *colorSequence);

int photocellVals[4]; //state of each of the photocells
int averageThreshold = 0;
const int LIT_THRESHOLD = 100;

boolean gameStarted = false;
boolean start = false;
// const int PRESS_ANGLE = 50; //angle at which servo will actuate to press button
// const int REST_ANGLE = 100; //angle at which servo will rest
// Servo servoCenter;
// Servo servoRed;
// Servo servoBlue;
// Servo servoYellow;
// Servo servoGreen;

int oldCounter = 0;

void setup()
{
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);


  //Attach servos to pins (need to figure out what pins. 10 is just an example)
  // servoCenter.attach(10);
  // servoRed.attach(10);
  // servoBlue.attach(10);
  // servoYellow.attach(10);
  // servoGreen.attach(10);
  // servoCenter.write(REST_ANGLE);
  // servoRed.write(REST_ANGLE);
  // servoBlue.write(REST_ANGLE);
  // servoYellow.write(REST_ANGLE);
  // servoGreen.write(REST_ANGLE);

  servoShield.begin();
  
  servoShield.setPWMFreq(PWMFreq);

}

void loop() {

  if (!gameStarted)
  {
    startGame();
    gameStarted = true;
  }
  /*
  read the pins to get their current light values
   reads from each photocell. Numbering convention:
   red - 0
   blue - 1
   yellow - 2
   green - 3
   */

  for (int i = 0; i < 4; i++)
  {
    int reading = analogRead(pinHolding[i]);
    if (reading - cellThresholds[i] > LIT_THRESHOLD /*some value*/)
    {
      colorSequence.push(i + 1);
      start = true;
      while (reading - cellThresholds[i] > LIT_THRESHOLD )
      {
        reading = analogRead(pinHolding[i]);
      }
    }
  }

  if ((colorSequence.count() == (oldCounter+1)) && start)
  {
    oldCounter = colorSequence.count();
    //Serial.println("Play!");
    Play(&colorSequence);
    start = false;
  }
}


void Play(QueueArray <int> *colorSequence)
{

  //Serial.print("Color sequence length:");
  Serial.println(colorSequence->count());
  while (!colorSequence->isEmpty())
  {
    actuateServo(colorSequence->pop());
  }

}

void actuateServo(int servoNum)
{
   /*
   I need to find out the max and min of the servos.
   For now I am setting them to the example settings.
   IF YOU ARE READING THIS, DO NOT RUN THIS CODE OR YOU MIGHT BREAK THE SERVOS.

   use this function to actuate the servo.
   servo numbering scheme:
   center - 0
   red - 1
   blue - 2
   yellow - 3
   green - 4
   */

  //center - 0 and 1, red - 2 and 3, blue - 4 and 5, yellow - 6 and 7, green - 8 and 9
  int maxMinValues[] = {150,600,150,600,150,600,150,600,150,600};
  int SERVOMIN = maxMinValues[servoNum*2];
  int SERVOMAX = maxMinValues[(servoNum*2) + 1];

  Serial.print("Servo num:");
  Serial.println(servoNum);

  //Push pushrod downwards.
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) 
  {
    servoShield.setPWM(servoNum, 0, pulselen);
  }

  //Bring push rod back up to starting posistion.
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) 
  {
    servoShield.setPWM(servoNum, 0, pulselen);
  }
}

void startGame()
{
  //we need to read all the sensors about 100 times. Get mode. This will calibrate each sensor for its own lighting conditions

  for (int i = 0; i < 4; i++)
  {
    Average<int> ave(100);
    for (int j = 0; j < 100; j++)
    {

      ave.push(analogRead(pinHolding[i]));
    }
    cellThresholds[i] = ave.mode();
    averageThreshold += cellThresholds[i];
  }
  averageThreshold = averageThreshold / 4;
  actuateServo(0);
}