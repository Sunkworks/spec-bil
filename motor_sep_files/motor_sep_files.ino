#include "motor.h"
#include "line.h"

const int lineSensorLeft = A1;
const int lineSensorRight = A0;

Motor right_motor(11, 10);
Motor left_motor(9, 3);
LaneFollower laneNav(lineSensorLeft, lineSensorRight);

void setup(){
  Serial.begin(9600);
  left_motor.setup();
  right_motor.setup();
  left_motor.setSpeed(200);
  right_motor.setSpeed(200);
  right_motor.setDirection(FORWARD);
  left_motor.setDirection(FORWARD);
  delay(100);
}

void rampSpeed(){
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

void StartupRush(){
  left_motor.setSpeed(255);
  right_motor.setSpeed(255);
  right_motor.setDirection(FORWARD);
  left_motor.setDirection(FORWARD);
  delay(3000);
  while (1 == 1){
    left_motor.setSpeed(0);
    right_motor.setSpeed(0);
    right_motor.setDirection(STOP);
    left_motor.setDirection(STOP);
    delay(1000);
  }
}

void loop() {

  int direction = laneNav.getTurnDirection();
  laneNav.printInfo();
  if (direction == TURN_LEFT){
    //right_motor.setDirection(FORWARD);
    //left_motor.setDirection(STOP);  
    right_motor.setSpeed(255);
    left_motor.setSpeed(200);
  }
  else if (direction == TURN_RIGHT){
    //right_motor.setDirection(STOP);
    //left_motor.setDirection(FORWARD);
    right_motor.setSpeed(200);
    left_motor.setSpeed(255);
  }
  else { // continue forward
    //right_motor.setDirection(FORWARD);
    //left_motor.setDirection(FORWARD); 
    right_motor.setSpeed(255);
    left_motor.setSpeed(255);   
  }
  delay(5);

}
