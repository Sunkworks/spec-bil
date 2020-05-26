#include "line.h"
#include <AccelStepper.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

enum states {
  TURNING_LEFT = 0,
  TURNING_RIGHT = 1,
  DRIVING_FORWARD = 2,
  ROTATING_LEFT = 3,
  ROTATING_RIGHT = 4,
  SCANNING_AREA = 5,  
};
int state;

// ULTRASOUND CONFIG
const int triggerPin = 2;
const int echoPin = 12;
const int MAX_DISTANCE = 350;
const int TRIGGER_DISTANCE = 5;
unsigned const int sonar_speed = 50;
unsigned long sonar_timer;
NewPing sonar(triggerPin, echoPin, MAX_DISTANCE);
enum directions { SONAR_LEFT = 0, SONAR_FORWARD = 1, SONAR_RIGHT = 2};
float distances[3]; // in cm


// LINE SENSORS
const int lineSensorLeft = A1;
const int lineSensorRight = A0;
LaneFollower laneNav(lineSensorLeft, lineSensorRight);

// MOTORS
const int navSpeed = 50;
const int TURN_STEP_COUNT = 107;
AccelStepper leftMotor(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
AccelStepper rightMotor(AccelStepper::FULL4WIRE, 5, 4, 6, 7);
const int servoPin = 3;
Servo servo;


void setup(){
  state = DRIVING_FORWARD;
  Serial.begin(9600);
  Serial.println("Starting program...");
  leftMotor.setMaxSpeed(200);
  rightMotor.setMaxSpeed(200);
  leftMotor.setSpeed(navSpeed);
  rightMotor.setSpeed(navSpeed);
  delay(100);
  distances[0] = distances[1] = distances[2] = MAX_DISTANCE;
  sonar_timer = millis();
  servo.attach(servoPin);
}

void checkStateTransitions(){
  if (state == TURNING_LEFT || state == TURNING_RIGHT || state == DRIVING_FORWARD){
    int direction = laneNav.getTurnDirection();
    switch (direction){
      case TURN_LEFT:
        state = TURNING_LEFT;
        leftMotor.setSpeed(0);
        rightMotor.setSpeed(navSpeed);
        break;
      case TURN_RIGHT:
        state = TURNING_RIGHT;
        leftMotor.setSpeed(navSpeed);
        rightMotor.setSpeed(0);
        break;
      case TURN_FORWARD:
        state = DRIVING_FORWARD; 
        leftMotor.setSpeed(navSpeed);
        rightMotor.setSpeed(navSpeed);
        break;
    }
  } 
  if (state == DRIVING_FORWARD){
    if (distances[SONAR_FORWARD] < TRIGGER_DISTANCE){
      state = SCANNING_AREA;
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
      // bool should_turn_left = ShouldTurnLeft();
      turn90(shouldTurnLeft());
       state = DRIVING_FORWARD;
      // determine turn direction, then enter that state
      // do scanning
      // stop motors
    }
    // check if entering scanning
    // if so, do timer_stop. turn on when leaving
  }
  laneNav.printInfo();
}

void loop() {
  checkStateTransitions();
  if (millis() >= sonar_timer){
    //sonar_timer += sonar_speed; // make sure that 
    sonar_timer = millis() + sonar_speed;
    measureDistanceForward();
  }
    
  switch (state){
    case TURNING_LEFT:    leftMotor.runSpeed();
                          rightMotor.runSpeed();
                          break;
    case TURNING_RIGHT:   leftMotor.runSpeed();
                          rightMotor.runSpeed();
                          break;
    case DRIVING_FORWARD: leftMotor.runSpeed();
                          rightMotor.runSpeed();
                          break;     
    case ROTATING_LEFT:   break;
    case ROTATING_RIGHT:  break;
    case SCANNING_AREA:   break;
  }  
  
  //Serial.println(state);
}

float safePing(){
  float distance = sonar.ping_cm(MAX_DISTANCE);
  return distance == 0 ? MAX_DISTANCE : distance;
}

void measureDistanceForward(){
  distances[SONAR_FORWARD] = safePing();  
  Serial.println(distances[SONAR_FORWARD]);
}


bool shouldTurnLeft(){
  servo.write(0);
  delay(500);
  float right_val = safePing();
  servo.write(180);
  delay(1000);
  float left_val = safePing();
  servo.write(90);
  return left_val > right_val;
}

void turn90(bool left){
  int steps = left ? TURN_STEP_COUNT : -TURN_STEP_COUNT;
  int dirSpeed = left ? navSpeed : -navSpeed;
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  leftMotor.move(steps);
  rightMotor.move(-steps);
  leftMotor.setSpeed(dirSpeed);
  rightMotor.setSpeed(-dirSpeed);
  while(leftMotor.distanceToGo() != 0 || rightMotor.distanceToGo() != 0){
    leftMotor.runSpeedToPosition();
    rightMotor.runSpeedToPosition();
    delay(1);
  }
}

void driveForward(unsigned int steps){
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  leftMotor.move(steps);
  rightMotor.move(steps);
  leftMotor.setSpeed(dirSpeed);
  rightMotor.setSpeed(dirSpeed);
  while(leftMotor.distanceToGo() != 0 || rightMotor.distanceToGo() != 0){
    leftMotor.runSpeedToPosition();
    rightMotor.runSpeedToPosition();
    delay(1);
  }
}
