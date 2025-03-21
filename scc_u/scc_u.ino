#include "scc_u.h"

State state = IDLE;
uint64_t lastUpdate;
uint32_t timer;
bool safetyON = true;
uint32_t distance;


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


  state = QUICK_SEARCHING;
}


void loop() {
  // check edge
  if(!(state == PUSHING && !safetyON)) {
      if(digitalRead(EDGE_S_L)) {
        if(digitalRead(EDGE_S_R)) {
          rotate(RIGHT, DEGREES_180);
          changeState(EVADING);
        }
        else {
          rotate(LEFT, DEGREES_120);
          changeState(EVADING);
        }
      }

      else if(digitalRead(EDGE_S_R)) {
          rotate(RIGHT, DEGREES_120);
          changeState(EVADING);
      }
  }


  switch(state) {

    case EVADING:
      if(digitalRead(SEARCH_S)) {
        x_stopMotors();
        changeState(LOCKED_IN);
        break;
      }

      if(getTimeElapsed() < timer) break;
      x_forward(255);

      if(getTimeElapsed() < EVADING_TIME) break;
      x_stopMotors();
      changeState(QUICK_SEARCHING);

      break;


    case QUICK_SEARCHING:
      if(digitalRead(SEARCH_S)) {
        changeState(LOCKED_IN);
      }

      else if(digitalRead(LEFT_S)) {
        rotate(LEFT, DEGREES_90);
        changeState(ROTATING);
      }

      else if(digitalRead(RIGHT_S)) {
        rotate(RIGHT, DEGREES_90);
        changeState(ROTATING);
      }

      else if(digitalRead(REAR_S)) {
        rotate(RIGHT, DEGREES_180);
        changeState(ROTATING);
      }
      else {
        x_right0(255);
        changeState(SEARCHING);
      }
      break;


  case SEARCHING:
    if(digitalRead(SEARCH_S)) {
      x_stopMotors();
      changeState(LOCKED_IN);
    }
    else if(getTimeElapsed() > SEARCH_TIMOUT) {
      \\TODO: this
    }
      break;


  case LOCKED_IN:
    getDistance();
    if(distance < PUSH_THRESHOLD) {
      x_forward(255);
      changeState(PUSHING);
    }
    else if(!digitalRead(SEARCH_S)) {
      changeState(QUICK_SEARCHING);
    }

    else if(distance < SIDE_ATTK_THRESHOLD) {
      x_arcTurn(128, 255);
      changeState(SIDE_ATTACKING);
    }

    else if(distance < APPROACH_THRESHOLD) {
      x_forward(128);
      changeState(APPROACHING);
    }
      break;


  case APPROACHING:
    if(!digitalRead(SEARCH_S)) {
      x_stopMotors();
      changeState(QUICK_SEARCHING);
      break;
    }

    getDistance();
    if(distance < PUSH_THRESHOLD) {
      x_forward(255);
      changeState(PUSHING);
    }
    else if(distance < SIDE_ATTK_THRESHOLD) {
      x_arcTurn(128, 255);
      changeState(SIDE_ATTACKING);
    }
      break;

  case SIDE_ATTACKING:
    if (getTimeElapsed() < SIDE_ATTK_TIMEOUT) break;
    
    if(digitalRead(SEARCH_S)) {
      x_forward(255);
      changeState(PUSHING);
    }
    else {
      x_stopMotors();
      changeState(QUICK_SEARCHING);
    }
      break;

  case PUSHING:
    if(!digitalRead(SEARCH_S)) {
      x_stopMotors();
      changeState(QUICK_SEARCHING);
    }
      break;


  case ROTATING:
    if(digitalRead(SEARCH_S)) {
      x_stopMotors();
      changeState(LOCKED_IN);
    }

    if(getTimeElapsed() > timer) {
      x_stopMotors();
      changeState(QUICK_SEARCHING);
    }
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


// max 6ms
int getDistance() {
  digitalWrite(DISTANCE_S_T, LOW);
  delayMicroseconds(2);
  
  digitalWrite(DISTANCE_S_T, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCE_S_T, LOW);
  
  // 58.3 us = 1 cm
  distance = pulseIn(DISTANCE_S_E, HIGH, DS_TIMEOUT);
} 


void rotate(byte direction, uint32_t degrees) {
  timer = degrees;
  if(direction)
    x_left0(255);
  else
    x_right0(255);
}











