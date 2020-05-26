#include "line.h"
#include <AccelStepper.h>
#include <AFMotor.h>


enum states {
  TURNING_LEFT = 0,
  TURNING_RIGHT = 1,
  DRIVING_FORWARD = 2,
  ROTATING_LEFT = 3,
  ROTATING_RIGHT = 4,
  SCANNING_AREA = 5,  
};

const int lineSensorLeft = A1;
const int lineSensorRight = A0;
const int navSpeed = 50;

int state;
LaneFollower laneNav(lineSensorLeft, lineSensorRight);
AccelStepper leftMotor(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
AccelStepper rightMotor(AccelStepper::FULL4WIRE, 4, 5, 6, 7);

void setup(){
  state = DRIVING_FORWARD;
  Serial.begin(9600);
  leftMotor.setMaxSpeed(200);
  rightMotor.setMaxSpeed(200);
  leftMotor.setSpeed(navSpeed);
  rightMotor.setSpeed(navSpeed);
  delay(100);
}

void checkStateTransitions(){
  int direction = laneNav.getTurnDirection();
  if (state == TURNING_LEFT || state == TURNING_RIGHT || state == DRIVING_FORWARD){
    switch (direction){
      case TURN_LEFT:     state = TURNING_LEFT; break;
      case TURN_RIGHT:    state = TURNING_RIGHT; break;
      case TURN_FORWARD:  state = DRIVING_FORWARD; break;
    }
  }
  // check ultrasound distance, if to close go into scan
  laneNav.printInfo();
}

void loop() {
  checkStateTransitions();
  switch (state){
    case TURNING_LEFT:    leftMotor.setSpeed(0);
                          rightMotor.setSpeed(navSpeed);
                          break;
    case TURNING_RIGHT:   leftMotor.setSpeed(navSpeed);
                          rightMotor.setSpeed(0);
                          break; 
    case DRIVING_FORWARD: leftMotor.setSpeed(navSpeed);
                          rightMotor.setSpeed(navSpeed);
                          break;          
  }  
  delay(5);
  leftMotor.runSpeed();
  rightMotor.runSpeed();
}
