const int lineSensorLeft = A1;
const int lineSensorRight = A0;


enum TurnDirection {
  TURN_LEFT = -1,
  TURN_FORWARD = 0,
  TURN_RIGHT = 1,
};

struct MovementInstruction {
  int throttle;
  int direction;
};


class LaneFollower {
  // Flesh out this class with so that it becomes general navigation class? ie obstacles etc
 private:
  // IO:
  byte _leftPin;
  byte _rightPin;
  // Internal Variables:
  int _leftVal;
  int _rightVal;
  // Sensitivity/control tweaks:
  const int _lineThreshold = 50;
  const int _LOWEST_TURN_VALUE = 55;
  
  int getTurnDirection(){
    if (_leftVal < _lineThreshold && _rightVal < _lineThreshold){
      return TURN_FORWARD;  
    }
    // todo: something else if both are activated
    return _leftVal > _rightVal ? TURN_RIGHT : TURN_LEFT;
  }
  
  int getThrottleIntensity(int turn){
    // turn: instance of TurnDirection enum
    // returns: output value between 0 and 255
    if (turn == TURN_FORWARD){
      return 255; 
    }
    int turn_urgency = (turn == TURN_LEFT) ? _rightVal : _leftVal; // determines which direction
    return map(turn_urgency, 50, 1023, _LOWEST_TURN_VALUE, 255);
  }
  
  void readSensors(){
    _leftVal = analogRead(_leftPin);
    _rightVal = analogRead(_rightPin);
  }
  
 public:
  // Constructor:
  LaneFollower(int leftPin, int rightPin) : _leftPin(leftPin), _rightPin(rightPin){}
 
  // Interface:
  // Usage: getNewMovementInstruction(&a, &b)
  void getNewMovementInstruction(int *direction, int *intensity){
    // TODO: use struct instead of pointers
    readSensors();
  *direction = getTurnDirection();
    *intensity = getThrottleIntensity(*direction);
  }
};

LaneFollower laneNav(lineSensorLeft, lineSensorRight);
void setup()
{
  Serial.begin(9600);
}

int instructionToInt(int dir, int intensity){
  if (dir == TURN_FORWARD)
    return 0;
  return dir == TURN_LEFT ? intensity : -intensity;
}

void loop()
{
  int direction, intensity;
  laneNav.getNewMovementInstruction(&direction, &intensity);
  Serial.println(instructionToInt(direction, intensity));
  delay(100);
}
