#include <ESP8266WiFi.h>

#include <Servo.h>

const char* ssid="ssid";
const char* password="pass";

const int switchPin = 14;

Servo servo;

WiFiServer server(80);
void setup() {
  // put your setup code here, to run once:
servo.attach(5); //servo
  pinMode(switchPin, INPUT_PULLUP);
servo.write(0);

Serial.begin(115200);
Serial.print("Connecting to.");
Serial.println(ssid);

WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);
while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print("..");}
Serial.println("Nodemcu(esp8266) is connected to the ssid");
Serial.println(WiFi.localIP());
 server.begin();
 delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  int val = digitalRead(switchPin);
 if(val==0){
    servo.write(90);
    delay(2000);
    servo.write(0);
    Serial.println("Tablet1_Dispensed!");
 }
 else{
   servo.write(0);
 }

WiFiClient client;
client=server.available();

if (client ==1){
  String request=client.readStringUntil('\n');
  client.flush();
  Serial.println(request);
  if (request.indexOf("Tablet1") != -1){
    servo.write(90);
    delay(2000);
    servo.write(0);
    client.println("HTTP/1.1 200 OK");
    Serial.println("Tablet1 Dispensed!");
    }

   else if (request.indexOf("Tablet2") != -1){
    client.println("HTTP/1.1 200 OK");
    Serial.println("Tablet2 Dispensed!");
    }

    Serial.print("Client Disconnected");
    Serial.println("===========================================================");
  Serial.println("                              ");
}
}