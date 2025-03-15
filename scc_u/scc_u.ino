#include "scc_u.h"

State state = IDLE;
unsigned long lastUpdate;
int timer;

void setup() {
  pinMode(EDGE_S_L, INPUT);
  pinMode(EDGE_S_R, INPUT);
  pinMode(REAR_S, INPUT);
  pinMode(LEFT_S, INPUT);
  pinMode(RIGHT_S, INPUT);
  pinMode(SWITCH_1,  INPUT_PULLUP);
  pinMode(SWITCH_2,  INPUT_PULLUP);
  pinMode(SWITCH_3,  INPUT_PULLUP);
  pinMode(SWITCH_180,  INPUT_PULLUP);
  pinMode(SEARCH_S, INPUT);
  pinMode(DISTANCE_S_T, INPUT);
  pinMode(DISTANCE_S_E, INPUT);

  delay(4900);
  if(digitalRead(SWITCH_180))
    xmotion.Right0(100, degrees(180));

  state = QUICK_SEARCHING;
  
}

void loop() {
  // check edge

  switch(state) {

    case QUICK_SEARCHING:
      if(digitalRead(SEARCH_S)) {
        changeState(LOCKED_IN);
      }

      else if(digitalRead(LEFT_S)) {
        rotate(degrees(90), LEFT);
        changeState(ROTATING);
      }

      else if(digitalRead(RIGHT_S)) {
        rotate(degrees(90), RIGHT);
        changeState(ROTATING);
      }

      else if(digitalRead(REAR_S)) {
        rotate(180, RIGHT);
        changeState(ROTATING);

      }
      break;

  case SEARCHING:
    if(digitalRead(SEARCH_S) == HIGH) {
      xmotion.StopMotors(0);
      changeState(LOCKED_IN);
    }

      break;

  case LOCKED_IN:
    if(getDistance() < PUSH_THRESHOLD) {
      xmotion.Forward(100, 0);
      changeState(PUSHING);
    }
    else if(!digitalRead(SEARCH_S)) {
      changeState(QUICK_SEARCHING);
    }
    else if(getDistance() < APPROACH_THRESHOLD) {
      xmotion.Forward(50, 0);
      changeState(APPROACHING);
    }
      break;

  case APPROACHING:
    if(getDistance() < PUSHING_THRESHOLD) {
      xmotion.Forward(100, 0);
      changeState(PUSHING);
    }
      break;

  case SIDE_ATTACKING:
      break;

  case PUSHING:
      break;

  case ROTATING:
    if(getTimeElapsed() > timer) {
      xmotion.StopMotors(0);
      changeState(QUICK_SEARCHING);
    }

      break;
  case EVADING:
      break;
    default: break;
  

  }

}





void changeState(State s) {
  state = s;
  lastUpdate = millis();
}



inline unsigned long getTimeElapsed() {
    return millis() - lastUpdate;
}












