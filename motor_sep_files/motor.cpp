#include "motor.h"
#include "Arduino.h"


Motor::Motor(int forward, int reverse) : forwardPin(forward), reversePin(reverse), 
  _direction(STOP), _speed(0){}

void Motor::setup(){
    pinMode(forwardPin, OUTPUT);
    pinMode(reversePin, OUTPUT);
    setDirection(STOP);
}

void Motor::updateMotors(){
    if (_direction == FORWARD){
        digitalWrite(reversePin, LOW);
        analogWrite(forwardPin, _speed);
    } else if (_direction == REVERSE){
        digitalWrite(forwardPin, LOW);
        analogWrite(reversePin, _speed);
    } else if (_direction == STOP){
        digitalWrite(forwardPin, LOW);
        digitalWrite(reversePin, LOW);
    }
}

void Motor::setDirection(int new_direction){
  _direction = new_direction;  
  updateMotors();
}
  
int Motor::getDirection() { return _direction; }

void Motor::setSpeed(int speed){
  if (speed > 255){
    Serial.println("Error, attempting to set speed greater than 255");
    return;
  }
  _speed = speed;
  updateMotors();
}
