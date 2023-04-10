#include <Stepper.h>

const int buttonPin = 2;
const int trigPin = 13;
const int echoPin = 12;
const int trigPin1 = 4;
const int echoPin1 = 3;
const float distanceThreshold = 30;
const int stepsPerRevolution = 2038;
const unsigned long durationThreshold = 2000;
int buttonState = 0;
int motorPosition = 0;

Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(buttonPin, INPUT);
  
  // Set the motor speed (in RPMs):
  myStepper.setSpeed(30);
}

void loop() {
   digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  float duration1 = pulseIn(echoPin1, HIGH);
  // Calculate the distance in centimeters
  float distance1 = duration1 / 58.0;
   // Print the distance on the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance1);
  Serial.println(" cm");

  // Check if the distance is less than the minimum distance
  if (distance1 < 5) {
    // Print the "bin full" message on the serial monitor
    Serial.println("Bin is full!");
  }

  // Wait for a short delay before taking another measurement
  delay(100);



  buttonState = digitalRead(buttonPin);
  
  // If the button is pressed:
  if (buttonState == HIGH) {
    // Move the motor by 90 degrees:
    myStepper.step(stepsPerRevolution / 4);
    // Update the motor position:
    motorPosition += 90;
    // Print the current motor position:
    // Wait for a moment:
    delay(5000);
    myStepper.step(-stepsPerRevolution / 4);
    motorPosition -= 90;
  }
  
}

void us_open(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  // Calculate the distance in centimeters
  float distance = duration / 58.0;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  // Check if a person is standing in front of the sensor
  if (distance <= distanceThreshold) {
    // Record the start time
    unsigned long startTime = millis();

    // Keep checking the distance for the duration threshold
    while (millis() - startTime <= durationThreshold) {
      // Measure the distance again
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance = duration / 58.0;

      // Check if the distance has increased
      if (distance > distanceThreshold) {
        break;
      }

      // Wait for a short period of time
      delay(50);
    }

    // Check if the duration threshold has been met
    if (millis() - startTime > durationThreshold) {
    // Activate the stepper motor
    myStepper.step(stepsPerRevolution / 4);
    // Update the motor position:
    motorPosition += 90;
    // Print the current motor position:
    // Wait for a moment:
    delay(5000);
    myStepper.step(-stepsPerRevolution / 4);
    motorPosition -= 90;
    
    }
  }
}
