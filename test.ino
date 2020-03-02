enum motorDirection {
    FORWARD,
    REVERSE,
    STOP
};

enum motorPins {
    motorForward = 11,
    motorReverse = 10
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
    digitalWrite(13, HIGH);
    changeMotorDirection(FORWARD);
    delay(1000);
    digitalWrite(13, LOW);
    changeMotorDirection(STOP);
    delay(1000);
    changeMotorDirection(REVERSE);
    delay(1000);

