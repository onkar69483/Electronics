#include <Servo.h>

Servo servo1; //this servo will rotate in the direction of the detected pothole
Servo servo2; //this servo will act for the mechanism of opening or closing the flow of cement/other material from the funnel

int trigPin1 = 22;  //declaring 5 ultrasonic sensors
int echoPin1 = 23;
int trigPin2 = 26;
int echoPin2 = 27;
int trigPin3 = 30;
int echoPin3 = 31;
int trigPin4 = 34;
int echoPin4 = 35;
int trigPin5 = 38;
int echoPin5 = 39;

long distance1; //distance measured by ultrasonic sensor
long duration1;

long distance2;
long duration2;

long distance3;
long duration3;

long distance4;
long duration4;

long distance5;
long duration5;

//code for bluetooth app and bot control
#define in1 13 //L298n Motor Driver pins.
#define in2 12
#define in3 11
#define in4 10

int command; //Int to store app command state.
int Speed = 204; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.

void setup() 

{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  
servo1.attach(7); // this servo rotates the funnel in the pothole direction.
servo2.attach(6);
  pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
 pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
 pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
 pinMode(echoPin5, INPUT);
 
 servo1.write(90); // starting position of the servo i.e. it faces front
 delay(1000);
 servo2.write(0); //closed state


 

}

void loop()

{
  app(); //calls the bluetooth app function/the car function
  ultra_sonic();
 if(distance1 >=10){          //if the distance of ultrasonic sensor 1 is > 10 i.e if pothole is detected, servo will rotate in that direction and stop.
  Stop(); // stops the car/roadbot
  servo1.write(0); //rotates the funnel/servo in the direction of the pothole
  delay(5000);
  servo2.write(90);    //It will open and start the flow of cement
  delay(100);
   if (distance1 <=10){       //after the pot gets filled with cement/any material then distance will be <10, then the servo will go back to its original position by stopping flow of cement.
    servo2.write(0) ;         //stops the flow of cement(closed state)
    delay(10000);              // this delay is there to stop the dripping of the cement
    servo1.write(90);        //servo rotates to its original position and the bot is ready to move further and detect other potholes
   }
 }
  if(distance2 >=10){         
  Stop(); 
  servo1.write(0); 
  delay(5000);
  servo2.write(90);    
  delay(100);
   if (distance2 <=10){       
    servo2.write(0) ;  
    delay(10000);      
    servo1.write(90);        
   }
 }
 if(distance3 >=10){        
  Stop(); 
  servo1.write(0);
  delay(5000);
  servo2.write(90);    
  delay(100);
   if (distance3 <=10){       
    servo2.write(0) ;   
    delay(10000);      
    servo1.write(90);        
   }
 }
 if(distance4 >=10){          
  Stop(); 
  servo1.write(0);
  delay(5000);
  servo2.write(90);   
  delay(100);
   if (distance4 <=10){       
    servo2.write(0) ; 
    delay(10000);       
    servo1.write(90);        
   }
 }
 if(distance5 >=10){          
  Stop(); 
  servo1.write(0); 
  delay(5000);
  servo2.write(90);    
  delay(100);
   if (distance5 <=10){       
    servo2.write(0) ;  
    delay(10000);       
    servo1.write(90);        
   }
 }


 
}

void ultra_sonic() //code for ultrasonic sensor

{

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1*0.034/2;

    digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*0.034/2;

    digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3*0.034/2;

    digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = duration4*0.034/2;

    digitalWrite(trigPin5, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH);
  distance5 = duration5*0.034/2;

  }

  void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}

void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}
void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);
}
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
}
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
}
void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void brakeOn() {
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  }
}
void brakeOff() {

}

void app(){
    if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //Initialize with motors stoped.
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
    }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}
