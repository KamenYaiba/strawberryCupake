#ifndef SCC_U_H
#define SCC_U_H


#include <xmotionV3.h>


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
#define PUSHING_THRESHOLD (45)
#define APPROACH_THRESHOLD (70)


#endif


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






