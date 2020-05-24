#include "line.h"
#include "Arduino.h"

int LaneFollower::getTurnDirection(){
  readSensors();
  if (_leftVal < _lineThreshold && _rightVal < _lineThreshold){
    return TURN_FORWARD;  
  }
  // todo: something else if both are activated
  return _leftVal > _rightVal ? TURN_RIGHT : TURN_LEFT;
}

int LaneFollower::getThrottleIntensity(int turn){
  // turn: instance of TurnDirection enum
  // returns: output value between 0 and 255
  if (turn == TURN_FORWARD){
    return 255; 
  }
  int turn_urgency = (turn == TURN_LEFT) ? _rightVal : _leftVal; // determines which direction
  return map(turn_urgency, 50, 1023, _LOWEST_TURN_VALUE, 255);
}

void LaneFollower::readSensors(){
  _leftVal = analogRead(_leftPin);
  _rightVal = analogRead(_rightPin);
}

LaneFollower::LaneFollower(int leftPin, int rightPin)
  : _leftPin(leftPin), _rightPin(rightPin){}

// Interface:
// Usage: getNewMovementInstruction(&a, &b)
void LaneFollower::getNewMovementInstruction(int *direction, int *intensity){
  // TODO: use struct instead of pointers
  readSensors();
*direction = getTurnDirection();
  *intensity = getThrottleIntensity(*direction);
}

void LaneFollower::printInfo(){
  Serial.print(_rightVal);
  Serial.print(",");              //seperator
  Serial.println(_leftVal);
}

int instructionToInt(int dir, int intensity){
  if (dir == TURN_FORWARD)
    return 0;
  return dir == TURN_LEFT ? intensity : -intensity;
}
