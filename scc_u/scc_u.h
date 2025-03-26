#include <xmiomod.h>


#ifndef SCC_U_H
#define SCC_U_H


#define degrees(x) ((x) / (6.0))

#define EDGE_S_L 0
#define EDGE_S_R 1
#define REAR_S A4
#define LEFT_S A5
#define RIGHT_S 4
#define SWITCH_1 5
#define SWITCH_2 6
#define SWITCH_3 7
#define SWITCH_180 A2
#define SEARCH_S 2
#define DISTANCE_S_T A1
#define DISTANCE_S_E 3


#define RIGHT 0
#define LEFT 1

#define DS_TIMEOUT (5988)
#define PUSH_THRESHOLD (800)
#define SIDE_ATTK_THRESHOLD (1500)
#define NOT_FOUND 32767

#define DEGREES_180 10
#define DEGREES_90 5
#define DEGREES_120 7
#define EVADING_TIME 10

#define SEARCH_TIMOUT 100
#define SIDE_ATTK_TIMEOUT 100






enum State {
  IDLE,
  QUICK_SEARCHING,
  SEARCHING,
  LOCKED_IN,
  APPROACHING,
  SIDE_ATTACKING,
  PUSHING,
  ROTATING,
  EVADING
};



#endif


