#include <AFMotor.h>

// Motor objects (Motor Shield)
AF_DCMotor motor1(1);   // Left motor
AF_DCMotor motor2(2);   // Right motor

// Ultrasonic pins
#define trigPin 9
#define echoPin 10

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  motor1.setSpeed(150);   // Speed (0–255)
  motor2.setSpeed(150);

  stopMotors();
}

void loop() {
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 15 && distance < 40) {
    moveForward();   // Human detected → follow
  }
  else {
    stopMotors();    // Too close or too far
  }

  delay(100);
}

// -------- FUNCTIONS --------

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 100; // no echo

  return duration * 0.034 / 2;
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
