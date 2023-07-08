#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include "HX711.h"

// Replace with your network credentials
const char* ssid = "";
const char* password = "";

// Replace with your server IP address or domain name
const char* serverName = "http://192.168.1.2";

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;

// Set web server port number to 80
WebServer server(80);

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  
  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  
  // Initialize the load cell
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-470);
  scale.tare();

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the web server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/data.csv", HTTP_GET, handleData);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Listen for incoming clients
  server.handleClient();

  // Measure the weight
  float weight = scale.get_units();

  // Check for stable reading
  if (millis() - currentTime > timeoutTime) {
    // If the reading is stable, save it to the file
    String data = String(weight) + "," + getTimeStamp() + "\n";
    File dataFile = SPIFFS.open("/data.csv", FILE_APPEND);
    if (dataFile) {
      dataFile.print(data);
      dataFile.close();
    }
    currentTime = millis();
  }
}

// Handle the root path
void handleRoot() {
  String html = "<!DOCTYPE html><html><body>";
  html += "<h1>Load Cell Data Logger</h1>";
  html += "<p>Weight: " + String(scale.get_units()) + " g</p>";
  html += "<p><a href=\"/data.csv\">Download data as CSV</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Handle the data path
void handleData() {
  File dataFile = SPIFFS.open("/data.csv", FILE_READ);
  if (dataFile) {
    server.streamFile(dataFile, "text/csv");
    dataFile.close();
  } else {
    server.send(404, "text/plain", "File not found");
  }
}

// Get the current date and time as a string
String getTimeStamp() {
  time_t now = time(nullptr);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
  return String(buffer);
}
