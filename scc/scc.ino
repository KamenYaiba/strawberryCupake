#include <xmotionV3.h>
#include "scc.h"

uint8_t mode; // 1: offensive, 2: defensive, 3: random

void (*reactionToDetection) ();


void setup() {
  Serial.begin(9600); // delete before deployment
  Serial.println("STARTTING...");

  pinMode(START, INPUT);
  pinMode(DipSwitch1, INPUT);
  pinMode(DipSwitch3, INPUT);

  pinMode(RIGHT_LINE_SENSOR, INPUT);
  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(LONG_IR, INPUT);
  pinMode(SHORT_IR, INPUT);

  attachInterrupt(digitalPinToInterrupt(RIGHT_LINE_SENSOR), rightSensorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(LEFT_LINE_SENSOR), leftSensorISR, RISING);

  mode = digitalRead(DipSwitch1) + 2 * digitalRead(DipSwitch3);

  switch(mode) {
    case OFFENSIVE: reactionToDetection = attack;
      break;
    case DEFENSIVE: reactionToDetection = avoid;
      break;
    case RANDOM: reactionToDetection = unexpectedResponse;
      break;
    default: Serial.println("ERROR: No mode selected");
  }

  

}

void loop() {
  // put your main code here, to run repeatedly:

}




void attack() {

}



void avoid() {

}


void unexpectedResponse() {
  if(random(0, 1))
    attack();
  else
    avoid();
}


void leftSensorISR() {

}


void rightSensorISR() {

}

















