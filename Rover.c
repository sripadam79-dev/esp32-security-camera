#include <Servo.h>
#include <NewPing.h>

#define SERVO_PIN 3
#define TRIG_PIN 11
#define ECHO_PIN 12

#define MAX_DISTANCE 200
#define DISTANCE_TO_CHECK 30

// 🔥 SPEED SETTINGS (TUNE HERE)
#define FORWARD_SPEED 180
#define BOOST_SPEED 140
#define REVERSE_SPEED 220
#define TURN_SPEED 255

// Right motor
int enR = 5;
int in1 = 7;
int in2 = 8;

// Left motor
int enL = 6;
int in3 = 9;
int in4 = 10;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myServo;

void setup() {
  pinMode(enR, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enL, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90);  // center
  delay(1000);

  moveMotor(0, 0);
}

void loop() {

  int distance = sonar.ping_cm();

  // Ignore false reading
  if (distance == 0) {
    distance = 100;
  }

  if (distance < DISTANCE_TO_CHECK) {

    // STOP
    moveMotor(0, 0);
    delay(300);

    // MOVE BACK (strong reverse)
    moveMotor(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(300);

    // STOP
    moveMotor(0, 0);
    delay(200);

    // SERVO SCAN
    myServo.write(140);
    delay(250);
    myServo.write(40);
    delay(250);
    myServo.write(90);
    delay(150);

    // TURN RIGHT (fast pivot)
    moveMotor(-TURN_SPEED, TURN_SPEED);
    delay(500);

    moveMotor(0, 0);
    delay(150);
  }
  else {

    // 🚀 BOOST START (helps overcome inertia)
    moveMotor(BOOST_SPEED, BOOST_SPEED);
    delay(30);

    // FAST FORWARD
    moveMotor(FORWARD_SPEED, FORWARD_SPEED);
  }
}

// MOTOR CONTROL FUNCTION
void moveMotor(int rightSpeed, int leftSpeed) {

  // Right motor direction
  if (rightSpeed >= 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  // Left motor direction
  if (leftSpeed >= 0) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  // Apply speed
  analogWrite(enR, abs(rightSpeed));
  analogWrite(enL, abs(leftSpeed));
}
