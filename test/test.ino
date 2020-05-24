enum motorDirection {
    FORWARD,
    REVERSE,
    STOP
};

enum motorPins {
    motorForward = 10,
    motorReverse = 11,
};
void setup(){
    pinMode(motorForward, OUTPUT);
    pinMode(motorReverse, OUTPUT);
    pinMode(13, OUTPUT);
}

void changeMotorDirection(motorDirection direction){
    if (direction == FORWARD){
        digitalWrite(motorReverse, LOW);
        digitalWrite(motorForward, HIGH);
    } else if (direction == REVERSE){
        digitalWrite(motorForward, LOW);
        digitalWrite(motorReverse, HIGH);
    } else if (direction == STOP){
        digitalWrite(motorForward, LOW);
        digitalWrite(motorReverse, LOW);
    }
}


void loop() {
    digitalWrite(motorReverse, LOW);
    digitalWrite(motorForward, HIGH);
    delay(1000);
}
