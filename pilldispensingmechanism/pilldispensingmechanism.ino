#include <Servo.h>

#define SERVO_PIN1 5
#define SERVO_PIN2 4
#define SERVO_PIN3 0

#define SWITCH_PIN1 2
#define SWITCH_PIN2 14
#define SWITCH_PIN3 12

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;

bool switchState1 = false;
bool switchState2 = false;
bool switchState3 = false;

int count1=1;
int count2=1;
int count3=1;

void setup() {
  pinMode(SWITCH_PIN1, INPUT_PULLUP);
  servoMotor1.attach(SERVO_PIN1);
  servoMotor1.write(0);
    pinMode(SWITCH_PIN2, INPUT_PULLUP);
  servoMotor2.attach(SERVO_PIN2);
  servoMotor2.write(0);
    pinMode(SWITCH_PIN3, INPUT_PULLUP);
  servoMotor3.attach(SERVO_PIN3);
  servoMotor3.write(0);
}

void loop() {
  switchState1 = digitalRead(SWITCH_PIN1);
  switchState2 = digitalRead(SWITCH_PIN2);
  switchState3 = digitalRead(SWITCH_PIN3);

  if (switchState1 == LOW) {
    count1++;
    delay(1000);
  }
  if (count1%2==0){
    servoMotor1.write(180);
  
  }
  else if(count1%2!=0){
    servoMotor1.write(0);
    
  }
  //-------------------------------------
   if (switchState2 == LOW) {
    count2++;
    delay(1000);
  }
  if (count2%2==0){
    servoMotor2.write(180);
  
  }
  else if(count2%2!=0){
    servoMotor2.write(0);
  //-------------------------------------
  }
   if (switchState3 == LOW) {
    count3++;
    delay(1000);
  }
  if (count3%2==0){
    servoMotor3.write(180);
  
  }
  else if(count3%2!=0){
    servoMotor3.write(0);
    
  }

}
