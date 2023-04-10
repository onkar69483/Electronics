// Include the necessary libraries
#include <Stepper.h>

const int stepsPerRevolution = 2048;  // Number of steps per revolution for the stepper motor
const int trigPin = 2;  // Arduino pin number for the trigger pin on the ultrasonic sensor
const int echoPin = 3;  // Arduino pin number for the echo pin on the ultrasonic sensor
const int distanceThreshold = 20;  // Distance threshold in centimeters
const int detectionTimeThreshold = 1000;  // Detection time threshold in milliseconds
int buttonPin = 4;
int buttonState = LOW;
int lastButtonState = LOW;
// initialize the motor direction
int motorDirection = 1;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // Initialize the stepper motor object
unsigned long detectionStartTime = 0;  // Variable to store the start time of object detection

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging purposes
  pinMode(trigPin, OUTPUT);  // Set the trigger pin as an output
  pinMode(echoPin, INPUT);  // Set the echo pin as an input
  myStepper.setSpeed(10);  // Set the speed of the stepper motor (in RPM)
  digitalWrite(buttonPin,LOW);
  
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  long duration, distance;
  buttonState = digitalRead(buttonPin);
   if (buttonState == HIGH && lastButtonState == LOW) {
    // change the motor direction
    
    // rotate the motor 90 degrees in the current direction
    myStepper.step(motorDirection * stepsPerRevolution / 4);
      motorDirection = -motorDirection;
  }
  
  // save the current button state
  lastButtonState = buttonState;
  
  // Send a 10 microsecond pulse to the trigger pin to start a measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the pulse on the echo pin and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Print the distance for debugging purposes
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check if the distance is less than the threshold
  if (distance < distanceThreshold) {
    // Check if object detection has just started
    if (detectionStartTime == 0) {
      detectionStartTime = millis();  // Store the start time of object detection
    } else {
      // Check if object has been in front of the ultrasonic sensor for more than the time threshold
      if (millis() - detectionStartTime >= detectionTimeThreshold && motorDirection==1) {
        // Rotate the stepper motor 90 degrees clockwise
        myStepper.step(stepsPerRevolution/4);
        
        // Wait for the object to move away from the ultrasonic sensor
        while (distance < distanceThreshold) {
          // Measure the distance again
        digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the pulse on the echo pin and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
          
          // Print the distance for debugging purposes
          Serial.print("Distance: ");
          Serial.print(distance);
          Serial.println(" cm");
        }
        
        // Rotate the stepper motor 90 degrees anticlockwise
        myStepper.step(-stepsPerRevolution/4);
        
        detectionStartTime = 0;  // Reset the start time of object detection
      }
    }
  } else {
    detectionStartTime = 0;  // Reset the start time of object detection
  }
}
