#include <xmiomod.h>

#define DISTANCE_S_T A1
#define DISTANCE_S_E 3



void setup() {
  pinMode(DISTANCE_S_T, OUTPUT);
  pinMode(DISTANCE_S_E, INPUT);
}

void loop() {
  testUS();
}



void testMotors(int dir, uint8_t speed) {
  if(dir)
    x_forward(speed);
  else
    x_backward(speed);
}





void testUS() {
  Serial.print("time: ");
  Serial.println(getDistance());
  
  delay(500);
}


int getDistance() {
  digitalWrite(DISTANCE_S_T, LOW);
  delayMicroseconds(2);
  
  digitalWrite(DISTANCE_S_T, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCE_S_T, LOW);
  
  // 58.3 us = 1 cm
  int distance = pulseIn(DISTANCE_S_E, HIGH, 9000);
  if(distance)
    return distance;

  return 35333;
} 




