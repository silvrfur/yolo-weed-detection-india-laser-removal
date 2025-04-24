#include <Servo.h>

// Motor Pins
const int motor1A = 3;
const int motor1B = 4;
const int motor2A = 5;
const int motor2B = 6;

// Ultrasonic Pins
const int trigPin = 9;
const int echoPin = 10;

// Servo Pins
const int servoXPin = 7;
const int servoYPin = 8;

// Laser Pin
const int laserPin = 11;

// Objects
Servo servoX;
Servo servoY;

void setup() {
  // Motor setup
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Laser
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);

  // Servos
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);
  servoX.write(90);
  servoY.write(90);

  Serial.begin(9600);
}

void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void stopMotors() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void fireLaser(int duration) {
  digitalWrite(laserPin, HIGH);
  delay(duration);
  digitalWrite(laserPin, LOW);
}

void aimAndFire(int angleX, int angleY, int fireDuration) {
  servoX.write(angleX);
  servoY.write(angleY);
  delay(500);
  fireLaser(fireDuration);
}

void loop() {
  // 🔁 Read Serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int comma1 = input.indexOf(',');
    int comma2 = input.lastIndexOf(',');

    if (comma1 > 0 && comma2 > comma1) {
      int angleX = input.substring(0, comma1).toInt();
      int angleY = input.substring(comma1 + 1, comma2).toInt();
      int duration = input.substring(comma2 + 1).toInt();

      stopMotors();
      aimAndFire(angleX, angleY, duration);
    }
  }

  // Obstacle detection
  long distance = getDistance();
  Serial.println("Distance: " + String(distance));
  if (distance > 20) {
    moveForward();
  } else {
    stopMotors();
  }
}
