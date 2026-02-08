#include <Servo.h>
Servo s1;
const int trigPin = 2;
const int echoPin = 3;
int currentAngle = 5;
int clearCounter = 0; // The "timer" variable
const int pauseTime = 100; // Increase this to make the pause longer
long duration;
int distanceCm, distanceInch;
void setup() {
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

s1.attach(4);   // Servo Motor

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  Serial.println("Distance: ");
  Serial.println(distanceCm);

  int targetAngle;
  if (distanceCm < 30 && distanceCm > 2) {
    clearCounter = 0;
   // Stay open if something is close

    if(currentAngle < 95) {
      currentAngle++;
      s1.write(currentAngle);
      delay(5);
    }
  } else {
    // We see nothing... so we wait!
    if (clearCounter < pauseTime) {
      clearCounter++; // Just count, don't move yet
  }

  else if (currentAngle > 5) {
    // ONLY close if nothing is in the way
    currentAngle--; // Move 1 degree toward 5
    s1.write(currentAngle);
    delay(15);      // Controls closing speed (slower is smoother)
    }
  }
}

