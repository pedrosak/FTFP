#include <Adafruit_MotorShield.h>   
#include <QTRSensors.h>  
#include <Encoder.h>

void DetermineChoices(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, QTRSensorsRC* qttrc,Encoder *encoderRight);
void Choose(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight);
void mapping();
void setupMappedNodes();
void setupMap();
void turnAround(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight);
void turnRight(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight);
void turnLeft(Adafruit_DCMotor *RM, Adafruit_DCMotor *LM, Encoder *encoderRight);
