#include <NewPing.h>
#include <Servo.h>

#define triggerPin 2
#define echoPin 3
#define servoPin 9
#define MAX_DISTANCE 350

NewPing sonar(triggerPin, echoPin, MAX_DISTANCE);

Servo ultrasound_servo;

float distance;

void setup(){
    Serial.begin(9600);
    ultrasound_servo.attach(servoPin);
}

void printDistance(float dist){
    Serial.print("Distance1 = ");
    Serial.println(dist);
}

float getDistance(NewPing sonar_sensor){
    
    float duration = sonar_sensor.ping();
    return duration * 0.0343/2;
}

void loop(){
    float farthest_distance = 0;
    float farthest_pos = 0;
    for (int pos = 0; pos <= 180; pos+= 10){
        ultrasound_servo.write(pos);
        delay(30); //wait for servo to rotate
        distance = getDistance(sonar);
        if (distance > farthest_distance){
            farthest_distance = distance;
            farthest_pos = pos;
        }
        delay(70);
    }
    printDistance(farthest_distance);
    Serial.print("at pos = ");
    Serial.println(farthest_pos);
    //ultrasound_servo.write(0);
    ultrasound_servo.write(farthest_pos);
    delay(1500);

}
