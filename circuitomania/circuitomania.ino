#include <Servo.h>
Servo servo1;
int trigPin = 9;
int echoPin = 8;
long distance;
long duration;
const int LED1 = A0;
const int LED2 = A1;
const int LED3 = A2;

 
void setup() 
{
servo1.attach(7); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);// put your setup code here, to run once:
 pinMode(LED1 , OUTPUT);
 pinMode(LED2 , OUTPUT);
 pinMode(LED3 , OUTPUT);

}
 
void loop() {
  ultra();
  servo1.write(0);
  if(distance <= 10){
  servo1.write(90);
  digitalWrite(LED1, LOW);
  delay(500);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  delay(500);
  digitalWrite(LED3, HIGH);
  
  }
  else
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    
  }
  
  delay(100);
}
 
void ultra(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  }
