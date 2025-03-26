#include "scc_u.h"

State state = IDLE;
uint64_t lastUpdate;
uint32_t timer;
bool safetyON = true;
uint32_t distance;


int lastState = 0;
char *snames[] = {"IDLE",
  "QUICK_SEARCHING",
  "SEARCHING",
  "LOCKED_IN",
  "APPROACHING",
  "SIDE_ATTACKING",
  "PUSHING",
  "ROTATING",
  "EVADING"};

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
  pinMode(DISTANCE_S_T, OUTPUT);
  pinMode(DISTANCE_S_E, INPUT);

  //delay(4900);
  //if(digitalRead(SWITCH_180))
  Serial.begin(9600);
  Serial.println("Start");



  state = QUICK_SEARCHING;
}


void loop() {
  // check edge
  if(!(state == PUSHING && !safetyON)) {
      if(!digitalRead(EDGE_S_L)) {
        if(!digitalRead(EDGE_S_R)) {
          rotate(RIGHT, DEGREES_180);
          changeState(EVADING);
        }
        else {
          rotate(LEFT, DEGREES_120);
          changeState(EVADING);
        }
      }

      else if(!digitalRead(EDGE_S_R)) {
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
    //else if(getTimeElapsed() > SEARCH_TIMOUT) {
      //TODO: this
    //}
      break;


    case LOCKED_IN:
      updateDistance();
      if(distance < PUSH_THRESHOLD) {
        x_forward(255);
        changeState(PUSHING);
      }

      else if(distance < SIDE_ATTK_THRESHOLD) {
        x_arcTurn(128, 255);
        changeState(SIDE_ATTACKING);
      }

      else{
        x_forward(128);
        changeState(APPROACHING);
      }

      if(!digitalRead(SEARCH_S)) {
        changeState(QUICK_SEARCHING);
      }
        break;


    case APPROACHING:
      if(!digitalRead(SEARCH_S)) {
        x_stopMotors();
        changeState(QUICK_SEARCHING);
        break;
      }

      updateDistance();
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
  debug();
}
  







void changeState(State s) {
  state = s;
  lastUpdate = millis();
}


inline unsigned long getTimeElapsed() {
    return millis() - lastUpdate;
}


// max 6ms
void updateDistance() {
  digitalWrite(DISTANCE_S_T, LOW);
  delayMicroseconds(2);
  
  digitalWrite(DISTANCE_S_T, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCE_S_T, LOW);
  
  // 58.3 us = 1 cm
  int tempDistance = pulseIn(DISTANCE_S_E, HIGH, DS_TIMEOUT);
  if(tempDistance)
    distance = tempDistance;
  else 
    distance = NOT_FOUND;
} 


void rotate(byte direction, uint32_t degrees) {
  timer = degrees;
  if(direction)
    x_left0(255);
  else
    x_right0(255);
}


void debugDelta() {
  char buffer[150];
  snprintf(buffer, sizeof(buffer),
           "%s | "
           "Right Speed: %3d | "
           "Left Speed %3d |"
           "Search IR: %d | "
           "Edge Left: %d | "
           "Edge Right: %d | "
           "Rear IR: %d | "
           "Left IR: %d | "
           "Right IR: %d | "
           "Ultrasonic Sensor: %4d",
           snames[state],
           x_rightMotorSpeed_DEBUG(),
           x_leftMotorSpeed_DEBUG(),
           digitalRead(SEARCH_S), 
           digitalRead(EDGE_S_L), 
           digitalRead(EDGE_S_R), 
           digitalRead(REAR_S), 
           digitalRead(LEFT_S), 
           digitalRead(RIGHT_S), 
           distance);
           
  Serial.println(buffer);
}


void debug() {
  char buffer[150];
  snprintf(buffer, sizeof(buffer),
           "State: %s\n"
           "Right Speed: %d\n"
           "Left Speed %d\n"
           "Search IR: %d\n"
           "Edge Left: %d\n"
           "Edge Right: %d\n"
           "Rear IR: %d\n"
           "Left IR: %d\n"
           "Right IR: %d\n"
           "Ultrasonic Sensor: %d",
           snames[state],
           x_rightMotorSpeed_DEBUG(),
           x_leftMotorSpeed_DEBUG(),
           digitalRead(SEARCH_S), 
           digitalRead(EDGE_S_L), 
           digitalRead(EDGE_S_R), 
           digitalRead(REAR_S), 
           digitalRead(LEFT_S), 
           digitalRead(RIGHT_S), 
           distance);

  Serial.println(buffer);
}


void getFrequency() {
  static long counter = 0;
  counter++;
  if(millis() > 10000) {
    Serial.println(counter);
  }
}











