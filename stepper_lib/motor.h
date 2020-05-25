#ifndef HEADER_MOTORCLASS
#define HEADER_MOTORCLASS

enum Direction {
  FORWARD = 1,
  STOP = 0,
  REVERSE = -1,
};

class Motor{
  private:
    int forwardPin;
    int reversePin;
    int _direction;
    int _speed;
  public:
    Motor(int forward, int reverse);
    void setup();
    void updateMotors();
    void setDirection(int new_direction);
    int getDirection();
    void setSpeed(int speed);
};

#endif
