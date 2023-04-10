#include <Stepper.h>

// Define number of steps per revolution
const int stepsPerRevolution = 2048;

// Initialize the stepper motor
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// Define pins for push switch and ultrasonic sensor
const int switchPin = 4;
const int trigPin = 2;
const int echoPin = 3;
int count = 0;

// Define variables for ultrasonic sensor
long duration;
int distance;

// Define variables for push switch
int switchState;
int lastSwitchState = LOW;
unsigned long switchPressTime = 0;

void setup() {
  // Set up serial communication for debugging
  Serial.begin(9600);

  // Set up pins for ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up pin for push switch
  pinMode(switchPin, INPUT_PULLUP);

  // Set up stepper motor speed and acceleration
  myStepper.setSpeed(100);
  myStepper.setAcceleration(600);
}

void loop() {
  // Read the state of the push switch
  switchState = digitalRead(switchPin);

  // Check if the push switch is pressed and start counting
  if (switchState == LOW && lastSwitchState == HIGH) {
    switchPressTime = millis();
  }

  // Check if the push switch has been held for more than 2 seconds
  if (switchState == LOW && millis() - switchPressTime > 2000) {
    rotateStepper();
    // Reset the switch press time
    switchPressTime = 0;
  }

  // Read the distance from the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Check if an object is detected for more than 2 seconds
  while(distance > 0 && distance < 100 && millis() - switchPressTime > 2000) {
    count++;
    if(count<=1){
    rotateStepper();
    }
  }

  // Save the last state of the push switch
  lastSwitchState = switchState;
}

void rotateStepper() {
  // Rotate the stepper motor 90 degrees clockwise
  myStepper.step(stepsPerRevolution / 4);

  // Wait for 5 seconds
  delay(5000);

  // Rotate the stepper motor 90 degrees anti-clockwise
  myStepper.step(-stepsPerRevolution / 4);

  // Wait for 5 seconds
  delay(5000);
}
