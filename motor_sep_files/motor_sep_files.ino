#include "motor.h"

Motor right_motor(11, 10);
Motor left_motor(5, 6);
void setup(){
  left_motor.setup();
  right_motor.setup();
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
}


void loop() {
  left_motor.setSpeed(255);
  right_motor.setSpeed(255);
  right_motor.setDirection(FORWARD);
  left_motor.setDirection(FORWARD);
  delay(3000);
  while (1 == 1){
    left_motor.setSpeed(0);
    right_motor.setSpeed(0);
    delay(1000);
  }
  while (0 == 1){
    left_motor.setDirection(FORWARD);
    right_motor.setDirection(FORWARD);
    delay(2000);
    left_motor.setDirection(REVERSE);
    right_motor.setDirection(REVERSE);
    delay(2000);
  }
  for(int i = 0; i < 0; i++){
    int speed = map(i, 0, 10, 0, 255);
    left_motor.setSpeed(speed);
    right_motor.setSpeed(speed);
    left_motor.setDirection(FORWARD);
    right_motor.setDirection(FORWARD);
    delay(2000);
    left_motor.setDirection(REVERSE);
    right_motor.setDirection(REVERSE);
    delay(2000);
  }
}
