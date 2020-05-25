#include "line.h"
#include <AccelStepper.h>
#include <AFMotor.h>

const int lineSensorLeft = A1;
const int lineSensorRight = A0;
const int navSpeed = 50;

LaneFollower laneNav(lineSensorLeft, lineSensorRight);
AccelStepper leftMotor(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
AccelStepper rightMotor(AccelStepper::FULL4WIRE, 4, 5, 6, 7);

void setup(){
  Serial.begin(9600);
  leftMotor.setMaxSpeed(200);
  rightMotor.setMaxSpeed(200);
  leftMotor.setSpeed(navSpeed);
  rightMotor.setSpeed(navSpeed);
  delay(100);
}

void loop() {
  int direction = laneNav.getTurnDirection();
  laneNav.printInfo();
  if (direction == TURN_LEFT){
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(navSpeed);
  }
  else if (direction == TURN_RIGHT){
      leftMotor.setSpeed(navSpeed);
      rightMotor.setSpeed(0);
  }
  else { // continue forward
    leftMotor.setSpeed(navSpeed);
    rightMotor.setSpeed(navSpeed);
  }
  delay(5);
  leftMotor.runSpeed();
  rightMotor.runSpeed();
}
