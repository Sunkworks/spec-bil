#include "line.h"
#include <AccelStepper.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#include <SPI.h>
#include <RFID.h>

enum states {
  TURNING_LEFT = 0,
  TURNING_RIGHT = 1,
  DRIVING_FORWARD = 2,
  ROTATING_LEFT = 3,
  ROTATING_RIGHT = 4,
  SCANNING_AREA = 5,  
  SCANNING_RFID = 6,
};
int state;

// ULTRASOUND CONFIG
const int triggerPin = 2;
const int echoPin = 8;
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
AccelStepper leftMotor(AccelStepper::FULL4WIRE, A5, A4, A3, A2);
AccelStepper rightMotor(AccelStepper::FULL4WIRE, 5, 4, 6, 7);
const int servoPin = 3;
Servo servo;

// RFID
const int SDAPin = 10;
const int resetPin = 9;
RFID rfid(SDAPin, resetPin);
enum rfid_instructions {
  RFID_RIGHT = 0,
  RFID_FORWARD = 1,
  RFID_LEFT = 2,
};
int rfid_instructions[256];
const int card0 = 0x42;
const int card1 = 0xC3;
const int card2 = 0x52;

const int RFID_TO_CENTER_STEPS = 75;
const int RFID_CENTER_TO_NORMAL_ROAD_STEPS = 100;


void setup(){
  rfid_instructions[card0] = RFID_RIGHT;
  rfid_instructions[card1] = RFID_FORWARD;
  rfid_instructions[card2] = RFID_LEFT;
  state = DRIVING_FORWARD;
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
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
        leftMotor.setSpeed(-navSpeed);
        rightMotor.setSpeed(navSpeed);
        break;
      case TURN_RIGHT:
        state = TURNING_RIGHT;
        leftMotor.setSpeed(navSpeed);
        rightMotor.setSpeed(-navSpeed);
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
    if (rfid.isCard()){
      if (rfid.readCardSerial()){
        driveForward(RFID_TO_CENTER_STEPS);
        switch(rfid_instructions[rfid.serNum[0]]){
          case RFID_RIGHT:  turn90(false); break;
          case RFID_LEFT:   turn90(true); break;
        }
        driveForward(RFID_CENTER_TO_NORMAL_ROAD_STEPS);
        state = DRIVING_FORWARD;
      }
    }
    // check if entering scanning
    // if so, do timer_stop. turn on when leaving
  }
  laneNav.printInfo();
}

void loop() {
  if (millis() >= sonar_timer){
    checkStateTransitions();
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
  leftMotor.setSpeed(navSpeed);
  rightMotor.setSpeed(navSpeed);
  while(leftMotor.distanceToGo() != 0 || rightMotor.distanceToGo() != 0){
    leftMotor.runSpeedToPosition();
    rightMotor.runSpeedToPosition();
    delay(1);
  }
}
