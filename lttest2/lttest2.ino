#include <SoftwareSerial.h>

SoftwareSerial espSerial(12, 13); // RX, TX

int LDR1 = A0; //for ldr sensors
int LDR2 = A1;
int LDR3 = A2;
int LDR4 = A3;
int Intensity = 1020;

int led1 = 18;
int led2 = 10;
int led3 = 11;
int led4 = 19;

int count = 4;


int A = 9; //for 7segment display
int B = 2;
int C = 3;
int D = 4;
int E = 5;
int F = 6;
int G = 7;
int P = 8;

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);

pinMode(LDR1, INPUT);  //LDR Pins
pinMode(LDR2, INPUT);
pinMode(LDR3, INPUT);

pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);

digitalWrite(led1, HIGH); 
digitalWrite(led2, HIGH); 
digitalWrite(led3, HIGH); 
digitalWrite(led4, HIGH); 

  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(A, LOW);
  digitalWrite(P, LOW);

for(int pin = 2;pin<10;pin++){ // 7Segment display pins
  pinMode(pin,OUTPUT);
}

  // Connect to Wi-Fi network
  sendCommand("AT+CWJAP=\"ssid\",\"pass\"");

  // Start server
  sendCommand("AT+CIPMUX=1");
  sendCommand("AT+CIPSERVER=1,80");
}

void zero(void){ //functions to print score on 7segment display
  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(A, LOW);
  digitalWrite(P, LOW);
}


void one(void){
 digitalWrite(A, HIGH);
 digitalWrite(B, LOW);
 digitalWrite(C, LOW);
 digitalWrite(D, HIGH);
 digitalWrite(E, HIGH);
 digitalWrite(F, HIGH);
 digitalWrite(G, HIGH);
  digitalWrite(P, LOW);
}
void two(void){
 digitalWrite(A, LOW);
 digitalWrite(B, LOW);
 digitalWrite(C, HIGH);
 digitalWrite(D, LOW);
 digitalWrite(E, LOW);
 digitalWrite(F, HIGH);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void three(void){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}

void four(void){
 digitalWrite(A, HIGH);
 digitalWrite(B, LOW);
 digitalWrite(C, LOW);
 digitalWrite(D, HIGH);
 digitalWrite(E, HIGH);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void five(void){
 digitalWrite(A, LOW);
 digitalWrite(B, HIGH);
 digitalWrite(C, LOW);
 digitalWrite(D, LOW);
 digitalWrite(E, HIGH);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void six(void){
 digitalWrite(A, LOW);
 digitalWrite(B, HIGH);
 digitalWrite(C, LOW);
 digitalWrite(D, LOW);
 digitalWrite(E, LOW);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void seven(void){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
 digitalWrite(D, HIGH);
 digitalWrite(E, HIGH);
 digitalWrite(F, HIGH);
 digitalWrite(G, HIGH);
  digitalWrite(P, LOW);
}


void eight(void){
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void nine(void){
 digitalWrite(A, LOW);
 digitalWrite(B, LOW);
 digitalWrite(C, LOW);
 digitalWrite(D, LOW);
 digitalWrite(E, HIGH);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}



void loop() {
  int ldr1Value = analogRead(LDR1);
  int ldr2Value = analogRead(LDR2);
  int ldr3Value = analogRead(LDR3);
  int ldr4Value = analogRead(LDR4);

  Serial.println("Intensity1: " + String(ldr1Value));
  Serial.println("Intensity2: " + String(ldr2Value));
  Serial.println("Intensity3: " + String(ldr3Value));
  Serial.println("Intensity4: " + String(ldr4Value)+"\n");

  
  // Check if any of the LDR sensors detects light
  if (ldr1Value > Intensity || ldr2Value > Intensity || ldr3Value > Intensity || ldr4Value > Intensity) {  //change the intensity '500' accordingly
    count--;
    Serial.println("Count: " + String(count));
  }
   if (ldr1Value > Intensity) { 
    digitalWrite(led1, LOW);  
  }
     if (ldr2Value > Intensity) { 
    digitalWrite(led2, LOW);     
  }
     if (ldr3Value > Intensity) { 
    digitalWrite(led3, LOW);   
  }
     if (ldr4Value > Intensity) { 
    digitalWrite(led4, LOW);   
  }
  
if (count == 0){ //Printing on 7 segment display
    zero();
    delay(1000);
  }
 else if (count == 1){
    one();
    delay(1000);
  }
 else if (count == 2){
    two();
    delay(1000);
  }
 else if (count == 3){
    three();
    delay(1000);
  }
 else if (count == 4){
    four();
    delay(1000);
  }
  else  if (count == 5){
    five();
    delay(1000);
  }

  
  
  // Listen for incoming client connections
  if (espSerial.available()) {
    String message = espSerial.readStringUntil('\n');
    Serial.println(message);
    if (message.indexOf("GET / ") != -1) {
      // Send HTML page with count value embedded
      sendResponse("<html><head><title>LDR Count</title></head><body><h1>LDR Count: " + String(count) + "</h1></body></html>");
    }
  }
}

void sendCommand(String command) {
  espSerial.println(command);
  delay(1000);
  while (espSerial.available()) {
    String response = espSerial.readStringUntil('\n');
    Serial.println(response);
  }
}

void sendResponse(String message) {
  String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  response += message;
  response += "\r\n";
  espSerial.print("AT+CIPSEND=0,");
  espSerial.println(response.length());
  delay(1000);
  espSerial.print(response);
  delay(1000);
}
