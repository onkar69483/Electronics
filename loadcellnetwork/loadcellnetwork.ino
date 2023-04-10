
// Load Wi-Fi library
#include <WiFi.h>
#include <Arduino.h>
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;

// Replace with your network credentials
const char* ssid = "Galaxy";
const char* password = "prem3562951413";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;



// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
            
  scale.set_scale(-470);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

            client.println("<!DOCTYPE html><html>");
            client.println("<body><h1>Weight: </h1>");
            client.print("<p>"+String(scale.get_units())+"g"+"</p>");
            client.println("</body></html>");
            scale.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
            
  
}
