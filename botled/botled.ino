#include "CTBot.h"
CTBot myBot;

String ssid = "";     
String pass = ""; 
String token = "5651849401:AAEdhpyEUdbYx8Wx9pxgJvFJBHEIwQAq2J";   

const int led1 = 13; 
int const trigPin = 4;
int const echoPin = 5;
int const buzzPin = 14;

TBMessage msg;

void setup() {
   
Serial.begin(115200);
Serial.println("Starting TelegramBot...");
myBot.wifiConnect(ssid, pass);
myBot.setTelegramToken(token);

if (myBot.testConnection()){
  Serial.println("\ntestConnection OK");
  myBot.sendMessage(msg.sender.id, "Wifi Connected!");
  myBot.sendMessage(msg.sender.id, "System has Started!");
}
else
  Serial.println("\ntestConnection NOK");

pinMode(led1, OUTPUT);
digitalWrite(led1, LOW); 
 
}

void loop() {
  
int duration, distance;
digitalWrite(trigPin, HIGH);
delay(1);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

if (distance <= 10 && distance >= 0) {
digitalWrite(buzzPin, HIGH);
digitalWrite(led1, HIGH);
myBot.sendMessage(msg.sender.id, "Alert!! Motion Detected");
} 

else {
digitalWrite(buzzPin, LOW);
digitalWrite(led1, LOW);
}

if (myBot.getNewMessage(msg)) {

  if (msg.text.equalsIgnoreCase("On")) {           
      digitalWrite(led1, HIGH);                             
      myBot.sendMessage(msg.sender.id, "LED is now ON"); 
      }
  else if (msg.text.equalsIgnoreCase("Off")) {        
      digitalWrite(led1, LOW);                              
      myBot.sendMessage(msg.sender.id, "LED1 is now OFF");
      }
      
    }
    delay(500);
}
