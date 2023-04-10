#include <ESP8266WiFi.h>
#include <Servo.h>
const char* ssid="Airtel_Galaxy";
const char* password="Prem@92484";

WiFiServer server(80);
Servo servo1,servo2,servo3;
int switch1 = 14, switch2 = 12, switch3 = 13;
void setup() {
  // put your setup code here, to run once:
servo1.attach(5); 
  pinMode(switch1, INPUT_PULLUP); 
servo2.attach(4); 
  pinMode(switch2, INPUT_PULLUP); 
servo3.attach(0); 
  pinMode(switch3, INPUT_PULLUP); 

Serial.begin(115200);
Serial.print("Connecting to.");
Serial.println(ssid);

WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);
while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print("..");}
Serial.println("Connected to Wifi!");
Serial.println(WiFi.localIP());
 server.begin();
 delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client;
client=server.available();
int val1 = digitalRead(switch1);
int val2 = digitalRead(switch2);
int val3 = digitalRead(switch3);
if (client ==1){
  String request=client.readStringUntil('\n');
  client.flush();
  Serial.println(request);
  if (request.indexOf("Tablet1") != -1 || val1 == 1){
  //servo code
    Serial.println("Tablet1 Init");}
  if (request.indexOf("Tablet2") != -1 || val2 == 1){
   //servo code
    Serial.println("Tablet2 Init");}
  if (request.indexOf("Tablet3") != -1 || val3 == 1){
  //servo code
    Serial.println("Tablet3 Init");}
  
    client.println("HTTP/1.1 200 OK");
    Serial.println("Tablet2 Init");}
    Serial.print("Client Disconnected");
    Serial.println("===========================================================");
  Serial.println("                              ");
}
