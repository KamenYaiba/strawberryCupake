#include <xmotionV3.h>
#include "scc_a.h"

uint8_t mode; // 1: offensive, 2: defensive, 3: random

bool safetyOn;

bool initialAvoid;

void (*reactionToDetection) ();

bool ddFlag = false;


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


  mode = digitalRead(DIPSWITCH1);
  initialAvoid = digitalRead(DIPSWITCH2);
  safetyOn = digitalRead(DIPSWITCH3);


  switch(mode) {
    case OFFENSIVE: reactionToDetection = attack;
      break;
    case RANDOM: reactionToDetection = unexpectedResponse;
      break;
  }

  if(safetyOn) {
    attachInterrupt(digitalPinToInterrupt(RIGHT_LINE_SENSOR), rightSensorISR, RISING);
    attachInterrupt(digitalPinToInterrupt(LEFT_LINE_SENSOR), leftSensorISR, RISING);
  }
  else {
    attachInterrupt(digitalPinToInterrupt(RIGHT_LINE_SENSOR), unsafeRightSensorISR, RISING);
    attachInterrupt(digitalPinToInterrupt(LEFT_LINE_SENSOR), unsafeLeftSensorISR, RISING);
  }
  
  attachInterrupt(digitalPinToInterrupt(SHORT_IR), detectionISR, RISING);


  delay(5000);  //RULE
  if(initialAvoid)
    moveToSide();

}


//this should run every 10 ms AT MAX
// keep delay() short
void loop() {
  if(ddFlag)
    deathDance();

  if(!digitalRead(LONG_IR))
    search();
  
  if(mode == OFFENSIVE)
    approach();

  if(digitalRead(SHORT_IR))
    attack();

}



void search() {
  xmotion.Left0(80, 0);
  while(!digitalRead(LONG_IR));
  xmotion.StopMotors(0);
}



//never call on loop()
void moveToSide() {
  if(random(0,2))
    xmotion.ArcTurn(60, 100, 80);
  else
    xmotion.ArcTurn(100, 60, 80);
}


void approach() {
  xmotion.Forward(30, 0);
}


void attack() {
    xmotion.Forward(100, 0);
}



void avoid() {
  xmotion.ArcTurn(100, 60, 50);
}


void deathDance() {
  ddFlag = false;
  xmotion.ArcTurn(80, 40, 200);
  xmotion.Left0(100, 40);
  xmotion.Forward(100, 50);
  xmotion.Left0(100, 40);
} 


void unexpectedResponse() {
  if(random(0, SPECIAL_MOVE_PROBABILITY))
    ddFlag = true;
  else
    attack();
}


void leftSensorISR() {
  if(digitalRead(RIGHT_LINE_SENSOR)) {
    xmotion.Right0(100, 60);
    xmotion.Forward(100, 40);
  }
  else {
    xmotion.Right0(100, 40); //120 angle
    xmotion.Forward(100, 40);
  }
}


void rightSensorISR() {
  if(digitalRead(LEFT_LINE_SENSOR)) {
    xmotion.Right0(100, 60);
    xmotion.Forward(100, 40);
  }
  else {
    xmotion.Left0(100, 40); //120 angle
    xmotion.Forward(100, 40);
  }
}


void unsafeLeftSensorISR() {
  if(!digitalRead(SHORT_IR)) {

    if(digitalRead(RIGHT_LINE_SENSOR)) {
      xmotion.Right0(100, 60);
      xmotion.Forward(100, 40);
    }
    else {
      xmotion.Right0(100, 40); //120 angle
      xmotion.Forward(100, 40);
    }

  }
}


void unsafeRightSensorISR() {
  if(!digitalRead(SHORT_IR)) {
    if(digitalRead(LEFT_LINE_SENSOR)) {
      xmotion.Right0(100, 60);
      xmotion.Forward(100, 40);
    }
    else {
      xmotion.Left0(100, 40); //120 angle
      xmotion.Forward(100, 40);
    }

  }

}


void detectionISR() {
  reactionToDetection();
}
















