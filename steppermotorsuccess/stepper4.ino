//Includes the Arduino Stepper Library
#include <Stepper.h>

#define PB 4


// Defines the number of steps per rotation
const int stepsPerRevolution = 509;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int c = 0;
void setup() {
  pinMode(PB, INPUT);
  digitalWrite(PB, HIGH);

}

void loop() {
  // Rotate CW slowly at 5 RPM
  if (digitalRead (PB) == LOW)
  {
    if (c == 0)
    {
      c = 1;
      myStepper.setSpeed(20);
      myStepper.step(stepsPerRevolution);
      delay(1000);
    }

    else
    {
      c = 0;

      // Rotate CCW quickly at 10 RPM
      myStepper.setSpeed(20);
      myStepper.step(-stepsPerRevolution);
      delay(1000);
    }
  }
}
