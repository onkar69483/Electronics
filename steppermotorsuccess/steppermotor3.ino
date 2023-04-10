// include the stepper library
#include <Stepper.h>

// define the pins for the stepper motor
#define STEPS 2048
#define IN1 8
#define IN2 1
#define IN3 9
#define IN4 11

// define the pin for the ultrasonic sensor
#define trigPin 2
#define echoPin 3

// define the pin for the button
#define buttonPin 4

// define the time in milliseconds for opening and closing the bin
#define openTime 2000
#define closeTime 2000

// create a stepper object
Stepper stepper(STEPS, IN1, IN3, IN2, IN4);

// initialize the ultrasonic sensor pins
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // initialize the button pin
  pinMode(buttonPin, INPUT_PULLUP);

  // set the motor speed in rpm
  stepper.setSpeed(10);
}

// main loop
void loop() {
  // read the distance from the ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // if there is someone standing in front of the bin for more than 2 seconds, open the bin
  if (distance < 30) {
    delay(2000); // wait for 2 seconds to confirm the person is standing there
    if (distance < 30) { // check again to make sure the person is still there
      openBin();
      while (distance < 30) {
        duration = pulseIn(echoPin, HIGH);
        distance = (duration / 2) / 29.1;
        delay(100); // delay for 100 milliseconds to prevent multiple openings
      }
      closeBin();
    }
  }

  // if the button is pressed, open or close the bin
  if (digitalRead(buttonPin) == LOW) {
    delay(10); // debounce the button
    if (digitalRead(buttonPin) == LOW) {
      if (stepper.currentPosition() == 0) {
        openBin();
      } else {
        closeBin();
      }
    }
    while (digitalRead(buttonPin) == LOW) {} // wait for the button to be released
  }
}

// function to open the bin
void openBin() {
  stepper.setSpeed(10);
  stepper.step(STEPS / 2);
  delay(openTime);
  stepper.setSpeed(100);
  stepper.step(STEPS / 2);
  stepper.setCurrentPosition(0);
}

// function to close the bin
void closeBin() {
  stepper.setSpeed(100);
  stepper.step(-STEPS / 2);
  delay(closeTime);
  stepper.setSpeed(10);
  stepper.step(-STEPS / 2);
  stepper.setCurrentPosition(0);
}
