
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

enum Direction {
  FORWARD = 1,
  STOP = 0,
  REVERSE = -1,
}


class Motor{
  private:
    AccelStepper _leftStepper(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
    AccelStepper _rightStepper(AccelStepper::FULL4WIRE, 4, 5, 6, 7);
    int _max_speed;
    int _speed;
    int _left_direction;
    int _right_direction;

  public:
    Motor(int max_speed) : _max_speed(max_speed) _speed(0){
        _leftStepper.setMaxSpeed(_max_speed);
        _leftStepper.setMaxSpeed(_max_speed);
      }
    void setup(); 
    void updateMotors(){ // has to be run every now and then
      _leftStepper.runSpeed();
      _rightStepper.runSpeed();

    }
    
    void setSpeed(int new_speed){
      _leftStepper.setSpeed(new_speed * _left_direction);
      _rightStepper.setSpeed(new_speed * _right_direction);
    }

    void setLeftDirection(int new_direction){
      _left_direction = new_direction;
    }
    
    void setRightDirection(int new_direction){
      _right_direction = new_direction;
    }
  
}



// initialize the stepper library on pins 8 through 11:


int stepCount = 0;         // number of steps the motor has taken

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  leftStepper.setMaxSpeed(250);
  leftStepper.setSpeed(100);
}

void loop() {
  // step one step:
  leftStepper.runSpeed();
  //leftStepper.step(1);
  //rightStepper.step(1);
  //Serial.print("steps:");
  //Serial.println(stepCount);
  //stepCount++;
  delay(10);
}
