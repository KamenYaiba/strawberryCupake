#include <xmiomod.h>


#ifndef SCC_U_H
#define SCC_U_H


#define degrees(x) ((x) / (6.0))

#define EDGE_S_L 0
#define EDGE_S_R 1
#define REAR_S 2
#define LEFT_S 3
#define RIGHT_S 4
#define SWITCH_1 5
#define SWITCH_2 6
#define SWITCH_3 7
#define SWITCH_180 A1
#define SEARCH_S A2
#define DISTANCE_S_T A4
#define DISTANCE_S_E A5


#define RIGHT 0
#define LEFT 1

#define DS_TIMEOUT (5988)
#define PUSH_THRESHOLD (30)
#define APPROACH_THRESHOLD (70)
#define SIDE_ATTK_THRESHOLD (45)


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


