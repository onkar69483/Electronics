#include <Servo.h>

Servo servo;

int switchPin = 2; // change to match your wiring
int switchState = 0;
int servoPosition = 0;

void setup() {
  servo.attach(9); // change to match your wiring
  pinMode(switchPin, INPUT_PULLUP); // change to match your wiring
}

void loop() {
  switchState = digitalRead(switchPin);
  
  if (switchState == LOW) {
    // switch is pressed
    if (servoPosition == 0) {
      // rotate 90 degrees clockwise
      servo.write(180);
      servoPosition = 1;
    } else {
      // rotate 90 degrees anti-clockwise
      servo.write(0);
      servoPosition = 0;
    }
    
    // wait for switch release
    while (digitalRead(switchPin) == LOW) {
      delay(10);
    }
  }
}
