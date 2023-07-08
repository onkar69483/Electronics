#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "ssid";
const char* password = "pass";

ESP8266WebServer server(80);

void handleRoot() {
  String message = "Hello from ESP8266!";
  server.send(200, "text/plain", message);
}

void handleData() {
  if (server.hasArg("data")) {
    String receivedData = server.arg("data");
    Serial.println("Received data: " + receivedData);
  }
  server.send(200, "text/plain", "Data received successfully");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/receive", handleData);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
