
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>
#include <AccelStepper.h>
#include <AFMotor.h>


const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:


int stepCount = 107;         // number of steps the motor has taken
int moveSpeed = 50;

const int navSpeed = 50;
const int TURN_STEP_COUNT = 107;
AccelStepper leftMotor(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
AccelStepper rightMotor(AccelStepper::FULL4WIRE, 5, 4, 6, 7);

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  leftMotor.setMaxSpeed(250);
//  leftStepper.setAcceleration(100);
  rightMotor.setMaxSpeed(250);
//  rightStepper.setAcceleration(100);
}

void loop() {
  // step one step:
  leftMotor.setSpeed(navSpeed);
  rightMotor.setSpeed(navSpeed);
  for (int i = 0; i < 10000; i++){
    leftMotor.runSpeed();
    rightMotor.runSpeed();
    delayMicroseconds(100);  
  }
  delay(1000);
  turn90(true);
  delay(2000);
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
  Serial.println("leaving turn90");
}
