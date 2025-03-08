#include <xmotionV3.h>
#include "scc.h"

uint8_t mode; // 1: offensive, 2: defensive, 3: random

bool specialMoveEnabled; //deathDance() for offensive and random, moveToSide() for defensive

void (*reactionToDetection) ();


void setup() {
  Serial.begin(9600); // delete before deployment
  Serial.println("STARTTING...");

  pinMode(START, INPUT);
  pinMode(DIPSWITCH1, INPUT);
  pinMode(DIPSWITCH2, INPUT);
  pinMode(DIPSWITCH3, INPUT);

  pinMode(RIGHT_LINE_SENSOR, INPUT);
  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(LONG_IR, INPUT);
  pinMode(SHORT_IR, INPUT);

  attachInterrupt(digitalPinToInterrupt(RIGHT_LINE_SENSOR), rightSensorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(LEFT_LINE_SENSOR), leftSensorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(SHORT_IR), detectionISR, RISING);

  mode = digitalRead(DIPSWITCH1) + 2 * digitalRead(DIPSWITCH2);
  specialMoveEnabled = digitalRead(DIPSWITCH3);

  switch(mode) {
    case OFFENSIVE: reactionToDetection = attack;
      break;
    case DEFENSIVE: reactionToDetection = avoid;
      if(specialMoveEnabled)
        moveToSide();
      break;
    case RANDOM: reactionToDetection = unexpectedResponse;
      break;
    default: Serial.println("ERROR: No mode selected"); exit(1);
  }

  delay(5000);  

}


//this should run every 10 ms AT MAX
// keep delay() short
void loop() {
  while(!digitalRead(START)); //busy waiting
  if(!digitalRead(LONG_IR))
    search();
  
  if(mode == OFFENSIVE)
    approach();

  if(digitalRead(SHORT_IR))
    attack();

}



void search() {

}


void moveToSide() {

}


void approach() {

}


void attack() {
  if(specialMoveEnabled && mode != DEFENSIVE && random(0, 2))
    deathDance();
  else
    xmotion.Forward(100, 1);
}



void avoid() {

}


void deathDance() {

} 


void unexpectedResponse() {
  if(random(0, AGGRESSION_LEVEL))
    attack();
  else
    avoid();
}


void leftSensorISR() {

}


void rightSensorISR() {

}


void detectionISR() {
  reactionToDetection();
}
















