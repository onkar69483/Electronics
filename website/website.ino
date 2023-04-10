#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// Replace with your network credentials
const char* ssid = "galaxy";
const char* password = "12345678";

ESP8266WebServer server(80);

void setup() {
  // Connect to Wi-Fi network
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Set up the web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}

void handleRoot() {
  String imageUrl = "http://example.com/image.jpg";
  http.begin(client, imageUrl);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String contentType = http.header("Content-Type");
    if (contentType.startsWith("image/")) {
      server.sendHeader("Content-Disposition", "inline; filename=image.jpg");
      server.sendHeader("Cache-Control", "max-age=31536000");
      server.sendHeader("Content-Type", contentType);
      server.sendHeader("Content-Length", http.getSize());
      server.send(200);
      http.writeToStream(&server);
    }
  }
  http.end();
}
