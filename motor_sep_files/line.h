#ifndef HEADER_LINECLASS
#define HEADER_LINECLASS

enum TurnDirection {
  TURN_LEFT = -1,
  TURN_FORWARD = 0,
  TURN_RIGHT = 1,
};


class LaneFollower {
  // Flesh out this class with so that it becomes general navigation class? ie obstacles etc
 private:
  // IO:
  int _leftPin;
  int _rightPin;
  // Internal Variables:
  int _leftVal;
  int _rightVal;
  // Sensitivity/control tweaks:
  const int _lineThreshold = 795;
  const int _LOWEST_TURN_VALUE = 55;
  

  
  int getThrottleIntensity(int turn);
  
  void readSensors();
  
 public:
  void printInfo();
   int getTurnDirection();
  LaneFollower(int leftPin, int rightPin);
 
  void getNewMovementInstruction(int *direction, int *intensity);
};

int instructionToInt(int dir, int intensity);

#endif
