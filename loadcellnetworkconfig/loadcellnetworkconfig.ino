#include <WiFi.h>
#include <Arduino.h>
#include "HX711.h"
#include <WiFiClientSecure.h>
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;
HX711 scale;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


const char* ssid = "Galaxy";    // name of your wifi network!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const char* password = "prem3562951413";     // wifi pasword !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const char* host = "https://script.google.com/macros/s/AKfycbxkJnbwAa7Dje7CB8Fz3Cb3MaOJ1v5klOV6fVH4HygqRTSweGd5w-03-d7iQPp_Jnh5zA/exec";
const int httpsPort = 443;
// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;
// SHA1 fingerprint of the certificate, don't care with your GAS service
const char* fingerprint = "953B48851E86EE233584FE72C3D01BE425FDA4DDFCEAB21BF4E4C412E947445B";
String GAS_ID = "AKfycbxkJnbwAa7Dje7CB8Fz3Cb3MaOJ1v5klOV6fVH4HygqRTSweGd5w-03-d7iQPp_Jnh5zA";   // Replace by your GAS service id           !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int iw;
void setup() 
{
  
  
  Serial.begin(115200); //Serial
     scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
       scale.set_scale(-71);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();          
  
  Serial.println();

  //connecting to internet
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 

}

void loop() 
{
  float w = scale.get_units();
  Serial.print("Weight = ");
  Serial.println(w);
   iw = (int) w;
  sendData(iw);
 
 delay(4000);
}

// Function for Send data into Google Spreadsheet
void sendData(int weight)
{
  client.setInsecure();
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
  Serial.println("certificate matches");
  } else {
  Serial.println("certificate doesn't match");
  }
  String string_weight =  String(weight, DEC);  
  String url = "/macros/s/" + GAS_ID + "/exec?weight=" + string_weight;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r") {
    Serial.println("headers received");
    break;
  }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
  Serial.println("esp8266/Arduino CI successfull!");
  } else {
  Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
} 
