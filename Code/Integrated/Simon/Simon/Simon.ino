#include <Servo.h>
#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
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
const int LIT_THRESHOLD = 100;

boolean gameStarted = false;
boolean start = false;

//PWM Frequency is set to example setting. Analog servo run at 60 Hz.
//Micro Servos operate at 60 Hz (Checked by Kurt)
const int PWMFreq = 60;

// our servo # counter
uint8_t servonum = 0;

//blue - 0 and 1, red - 2 and 3, green - 4 and 5, yellow - 6 and 7, center - 8 and 9
//center servo not mounted. Max/Min (maxMinValues 8 and 9) not set yet.
int maxMinValues[] = {230,310,230,310,230,310,370,480,100,600};

int oldCounter = 0;

void setup()
{
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
  servoShield.begin();
  servoShield.setPWMFreq(PWMFreq);

  //Puts all servos in the UP position
  initializeServo();

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
   blue - 0
   red - 1
   green - 2
   yellow - 3
   center - 4
   */

   /* //Test Code\\
   int test[] = {3,0,2,1};
   for (int i = 0; i < 4; i++)
   {
    colorSequence.push(test[i]);
    start = true;
   }

  if ((colorSequence.count()) && start)
  {
    oldCounter = colorSequence.count();
    Play(&colorSequence);
    start = false;
  }
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
    Current simon says interrector : Version 1 (2 by 4 and hammer version)
    All 4 Micro servos have been tested. Center servo is not mounted and still
    missing Max/Min (Kurt, March 29)

   use this function to actuate the servo.
   servo numbering scheme:
   blue - 0
   red - 1
   green - 2
   yellow - 3
   center - 4
   */
  
  //Fetches servos min and max from maxMinValues array.
  int SERVOMIN = maxMinValues[servoNum*2];
  int SERVOMAX = maxMinValues[(servoNum*2) + 1];

  Serial.print("Servo num:");
  Serial.println(servoNum);

  //Bring push rod back up to starting posistion.
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) 
  {
    servoShield.setPWM(servoNum, 0, pulselen);
  }

  //Push pushrod downwards.
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
  }
  actuateServo(4);
}


//Initializes servo to up position
//Need to add a 5th servo for center servo which has not been installed yet (kurt)
void initializeServo() 
{
  int number_of_servos = 4;

  for(int z = 0; z < number_of_servos; z++) 
  {
    int minVals = maxMinValues[z*2];
    int maxVals = maxMinValues[(z*2) + 1];
    for (uint16_t pulselen = minVals; pulselen < maxVals; pulselen++) 
  {
    servoShield.setPWM(z, 0, pulselen);
  }
  }
}
