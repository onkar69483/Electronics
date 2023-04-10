// Include the necessary libraries
#include <Stepper.h>

// Define constants for the stepper motor
const int stepsPerRevolution = 2048;
const int motorPin1 = 8;
const int motorPin2 = 9;
const int motorPin3 = 10;
const int motorPin4 = 11;

// Define the ultrasonic sensor and push switch pins
const int trigPin = 3;
const int echoPin = 2;
const int switchPin = 4;

// Define variables to store the distance and switch state
long duration;
int distance;
int switchState;

// Create an instance of the stepper motor object
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);

void setup() {
  // Initialize the ultrasonic sensor and push switch pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(switchPin, INPUT);

  // Set the speed of the stepper motor
  myStepper.setSpeed(60);

  // Serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {
  // Get the distance from the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Get the state of the push switch
  switchState = digitalRead(switchPin);

  // Check if something is detected for more than 2 seconds or the push switch is pressed
  if (distance > 0 && distance < 50 || switchState == HIGH) {
    // Rotate the stepper motor 90 degrees clockwise
    myStepper.step(stepsPerRevolution/4);
    delay(5000);
    // Rotate the stepper motor 90 degrees anti-clockwise
    myStepper.step(-stepsPerRevolution/4);
    delay(5000);
  }

  // Serial communication for debugging purposes
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(", Switch: ");
  Serial.println(switchState);
}
