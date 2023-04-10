// include the libraries needed for the project
#include <Stepper.h>

// define constants for the motor
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution for your motor
const int clockwiseDirection = 1;   // change this to fit the direction of rotation for your motor
const int antiClockwiseDirection = -1;

// initialize the stepper motor
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // change the pins to match your wiring

// define constants for the ultrasonic sensor
const int trigPin = 2;    // change this to match your wiring
const int echoPin = 3;    // change this to match your wiring
const long timeout = 2000; // maximum time to wait for the ultrasonic pulse to return, in microseconds
const int buttonpin = 4;
int buttonstate = 0;
void setup() {
  // initialize the serial port for debugging purposes
  Serial.begin(9600);

  // set up the pins for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonpin, INPUT_PULLUP);

  // set up the motor pins
  myStepper.setSpeed(30); // adjust this value to fit your motor's capabilities
}

void loop() {
  // trigger the ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // wait for the ultrasonic pulse to return
  long duration = pulseIn(echoPin, HIGH, timeout);

  // calculate the distance based on the duration of the ultrasonic pulse
  int distance = duration * 0.034 / 2;

  // check if the distance is less than 10 cm (adjust this value to fit your needs)
  if (distance < 10 || digitalRead(buttonpin)==0) {
    Serial.println("Object detected!");

    // rotate the motor 90 degrees clockwise
    myStepper.step(stepsPerRevolution / 4 * clockwiseDirection);

    // wait for 5 seconds
    delay(5000);

    // rotate the motor 90 degrees anti-clockwise
    myStepper.step(stepsPerRevolution / 4 * antiClockwiseDirection);

    // wait for 5 seconds
    delay(5000);
  }
}
