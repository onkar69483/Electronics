#include <Stepper.h>

// Define number of steps per revolution
const int stepsPerRevolution = 2048;

// Initialize the stepper motor
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// Define pins for push switch and ultrasonic sensor
const int switchPin = 4;
const int trigPin = 2;
const int echoPin = 3;
int flag1 = 0;
int flag2 = 0;

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
 digitalWrite(switchPin,HIGH);
  // Set up stepper motor speed and acceleration
  myStepper.setSpeed(10);
 
}

void loop() {
  // Read the state of the push switch
  switchState = digitalRead(switchPin);

  // Check if the push switch is pressed and start counting
  if (switchState == LOW && lastSwitchState == HIGH) {
    switchPressTime = millis();
  }

  // Check if the push switch has been held for more than 2 seconds
  if (switchState == LOW ) {
    if(flag2 ==0){
      flag2=1;
      myStepper.step(stepsPerRevolution/4);
 
    }
    else{
      flag2=0;
      myStepper.step(-stepsPerRevolution/4);
      
    }
    
    rotateStepper();
    // Reset the switch press time
    switchPressTime = 0;
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;


    flag1=0;
    while(distance<20 && millis() - switchPressTime > 5000){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println("inside loop");
 flag1++;
  if(flag1==1){
    rotateStepper();
    delay(500);
  }
 if(distance>20 && flag1>0){
    myStepper.step(-stepsPerRevolution/4);
    delay(500);
    break;
   }
  }
 Serial.println("outside");
 delay(500);
 


  // Save the last state of the push switch
  lastSwitchState = switchState;
}

void rotateStepper() {
  // Rotate the stepper motor 90 degrees clockwise
  myStepper.step(stepsPerRevolution / 4);

  // Wait for 5 seconds
  delay(500);

}
