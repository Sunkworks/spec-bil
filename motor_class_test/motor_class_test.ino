enum Direction {
  FORWARD = 1,
  STOP = 0,
  REVERSE = -1,
};



class Motor {
  private:
    int forwardPin;
    int reversePin;
    int _direction;
    int _speed;
  public:
    Motor(int forward, int reverse) : forwardPin(forward), reversePin(reverse), 
  _direction(STOP), _speed(0){}
  void setup(){
    pinMode(forwardPin, OUTPUT);
    pinMode(reversePin, OUTPUT);
    setDirection(STOP);
  }
  void updateMotors(){
    if (_direction == FORWARD){
        analogWrite(reversePin, 0);
        analogWrite(forwardPin, _speed);
    } else if (_direction == REVERSE){
        analogWrite(forwardPin, 0);
        analogWrite(reversePin, _speed);
    } else if (_direction == STOP){
        analogWrite(forwardPin, 0);
        analogWrite(reversePin, 0);
    }
  }
  
  void setDirection(int new_direction){
    _direction = new_direction;  
    updateMotors();
  }
  
  int getDirection() { return _direction; }
  void setSpeed(int speed){
    if (speed > 255){
      Serial.println("Error, attempting to set speed greater than 255");
      return;
    }
    _speed = speed;
    updateMotors();
  }
  
};


Motor right_motor(11, 10);
Motor left_motor(5, 6);
void setup(){
  left_motor.setup();
  right_motor.setup();
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
}


void loop() {
  left_motor.setSpeed(255);
  right_motor.setSpeed(255);
  right_motor.setDirection(FORWARD);
  left_motor.setDirection(FORWARD);
  delay(3000);
  while (1 == 1){
    left_motor.setSpeed(0);
    right_motor.setSpeed(0);
    delay(1000);
  }
  while (0 == 1){
    left_motor.setDirection(FORWARD);
    right_motor.setDirection(FORWARD);
    delay(2000);
    left_motor.setDirection(REVERSE);
    right_motor.setDirection(REVERSE);
    delay(2000);
  }
  for(int i = 0; i < 0; i++){
    int speed = map(i, 0, 10, 0, 255);
    left_motor.setSpeed(speed);
    right_motor.setSpeed(speed);
    left_motor.setDirection(FORWARD);
    right_motor.setDirection(FORWARD);
    delay(2000);
    left_motor.setDirection(REVERSE);
    right_motor.setDirection(REVERSE);
    delay(2000);
  }
}
