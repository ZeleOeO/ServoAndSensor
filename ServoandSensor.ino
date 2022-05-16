#include <Servo.h>

Servo myservo; // Creating a servo object
int pos = 0; // The angle of the Servo
int trigPin = 9; // TrigPin for the ultrasonic sensor
int echoPin = 8; // EchoPin for the ultrasonic sensor

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // The TrigPin is an OUTPUT pin because it releases sound waves
  pinMode(echoPin, INPUT); // The EchoPin is an INPUT pin because it receives the waves when it's bounced
  myservo.attach(11); // The Pin of the Servo
}

void loop() {
  int distance = DistanceSensor();
  Servo(distance);
}

// Created two functions for Both the sensor and the Servo
int DistanceSensor() {
  // Declaring Variables
  long duration; // For the duration of the time the sound wave travelled
  int distance; // The distance 
  digitalWrite(trigPin, LOW); // Deactivates the trig
  delayMicroseconds(10); // Waits for a hundredth of a second
  digitalWrite(trigPin, HIGH); // Activates the trig
  delayMicroseconds(10); // Waits for a hundredth of a second
  digitalWrite(trigPin, LOW); // Deactivates the trig
  duration = pulseIn(echoPin, HIGH); // Equates the duration to the time the waves were recieved by the echopin
  // Calculates the distance by using; distance = time * speed
  // Speed of sound is 0.0034cm/s, then divide by 2 for the echo
  distance = duration * 0.034/2;
  return distance; // returns distance
}

void Servo (int distance) {
  // If distance < 200 then the pos/angle = 0
  if (distance <= 200) {
    pos = 0;
    myservo.write(pos);
  }
  // If distance > 200 then the pos/angle = 90
  else {
    pos = 90;
    myservo.write(pos);
    }
}
