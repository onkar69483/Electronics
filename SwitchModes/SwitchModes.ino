#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

const int buttonPin = 14; // Pin 14 for the button

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Hi</h1>");
}


 String handleConfig = ""
"<html><head><title>ScoboBot WiFi Configuration</title></head><body>"
"<div style='display: flex; justify-content: center; align-items: center; height: 100vh;'>"
"<div style='background-color: #f2f2f2; padding: 20px; border-radius: 5px;'>"
"<h1>WiFi Configuration</h1>"
"<form method='POST' action='/saveconfig'>"
"<label for='ssid'>SSID:</label><br>"
"<input type='text' id='ssid' name='ssid' style='width: 250px; padding: 10px;'><br><br>"
"<label for='password'>Password:</label><br>"
"<input type='password' id='password' name='password' style='width: 250px; padding: 10px;'><br><br>"
"<input type='submit' value='Save' style='padding: 10px 20px; background-color: #4CAF50; color: white; border: none; border-radius: 4px; cursor: pointer;'>"
"</form>"
"</div>"
"</div>"
"<style>body { font-family: Arial, sans-serif; }</style></body></html>"; // Add a basic font-family style


void handleSaveConfig() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  // Save the new WiFi credentials
  saveWiFiCredentials(ssid, password);
    Serial.println("Credentials Saved!");
String html = "<html><head><title>ScoboBot WiFi Configuration</title></head><body>";
  html += "<div style='display: flex; justify-content: center; align-items: center; height: 100vh;'>";
  html += "<div style='background-color: #f2f2f2; padding: 20px; border-radius: 5px;'>";
  html += "<h1 style='color: #4CAF50;'>Configuration Saved!</h1>";
  html += "<p>Your WiFi configuration has been saved successfully.</p>";
  html += "<p>Please restart the device to apply the new settings.</p>";
  html += "<p>Also press config switch to turn off config mode!</p>";
  html += "</div>";
  html += "</div>";
  html += "<style>body { font-family: Arial, sans-serif; }</style></body></html>"; // Add a basic font-family style
  server.send(200, "text/html", html);
}

void saveWiFiCredentials(const String& ssid, const String& password) {
  // Save the WiFi credentials to EEPROM
  int ssidLength = ssid.length() + 1;
  int passwordLength = password.length() + 1;

  EEPROM.begin(512);
  EEPROM.write(0, ssidLength);
  for (int i = 0; i < ssidLength; ++i) {
    EEPROM.write(i + 1, ssid[i]);
  }
  EEPROM.write(ssidLength + 1, passwordLength);
  for (int i = 0; i < passwordLength; ++i) {
    EEPROM.write(ssidLength + 2 + i, password[i]);
  }
  EEPROM.commit();
  EEPROM.end();
}

void loadWiFiCredentials(String& ssid, String& password) {
  // Load the WiFi credentials from EEPROM
  EEPROM.begin(512);
  int ssidLength = EEPROM.read(0);
  for (int i = 0; i < ssidLength; ++i) {
    ssid += char(EEPROM.read(i + 1));
  }
  int passwordLength = EEPROM.read(ssidLength + 1);
  for (int i = 0; i < passwordLength; ++i) {
    password += char(EEPROM.read(ssidLength + 2 + i));
  }
  EEPROM.end();
}

void setup() {
  Serial.begin(115200);
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Check if the button is pressed during startup
  if (digitalRead(buttonPin) == LOW) {
    delay(1000);
    // If the button is pressed, enter WiFi configuration mode
    Serial.println("Entering WiFi configuration mode!");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("ScoboBot_WifiConnect"); // Create an access point
    IPAddress apIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(apIP);
    dnsServer.start(DNS_PORT, "*", apIP);
    if (MDNS.begin("scobobot")) {
    Serial.println("MDNS responder started");
  }
    server.onNotFound([]() {
    server.send(200, "text/html", handleConfig);
  });
    server.on("/saveconfig", handleSaveConfig);
  } else {
    // If the button is not pressed, load WiFi credentials and connect to WiFi
    String ssid, password;
    loadWiFiCredentials(ssid, password);
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.on("/", handleRoot);
  }
  
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  if(digitalRead(buttonPin) == LOW){
    MDNS.update();
    dnsServer.processNextRequest();
  }
  server.handleClient();
}