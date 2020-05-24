#define RIGHT_LINE_PIN 0
#define LEFT_LINE_PIN 1


void setup() {
  Serial.begin(9600);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  int right_line = analogRead(RIGHT_LINE_PIN);
  int left_line = analogRead(LEFT_LINE_PIN);
  Serial.print(right_line);
  Serial.print(",");              //seperator
  Serial.println(left_line);
  delay(100);

}
