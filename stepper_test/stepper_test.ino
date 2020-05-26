
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

AccelStepper leftStepper(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
AccelStepper rightStepper(AccelStepper::FULL4WIRE, 4, 5, 6, 7);

// initialize the stepper library on pins 8 through 11:


int stepCount = 95;         // number of steps the motor has taken
int moveSpeed = 50;

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  leftStepper.setMaxSpeed(250);
//  leftStepper.setAcceleration(100);
  rightStepper.setMaxSpeed(250);
//  rightStepper.setAcceleration(100);
}

void loop() {
  // step one step:
  if (leftStepper.distanceToGo() == 0){
    leftStepper.disableOutputs();   
  }
  if (rightStepper.distanceToGo() == 0){
    rightStepper.disableOutputs();   
  }
  leftStepper.moveTo(stepCount);
  rightStepper.moveTo(-stepCount);
  leftStepper.setSpeed(moveSpeed);
  rightStepper.setSpeed(moveSpeed);
  leftStepper.runSpeedToPosition();
  rightStepper.runSpeedToPosition();
  //leftStepper.step(1);
  //rightStepper.step(1);
  //Serial.print("steps:");
  //Serial.println(stepCount);
  //stepCount++;
  delay(10);
}
