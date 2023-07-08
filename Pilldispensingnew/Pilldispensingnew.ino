#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "ssid";  // Replace with your network name
const char* password = "pass";  // Replace with your network password

WiFiServer server(80);
Servo servo;

void setup() {
  Serial.begin(115200);
  servo.attach(D2); // Attach servo signal wire to D2 pin
  pinMode(D1, INPUT_PULLUP); // Configure D1 as input pin with internal pull-up resistor
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected.");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        int value = digitalRead(D1);
        String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        response += "<!DOCTYPE HTML>\r\n<html>\r\n";
        response += "<button onclick=\"location.href='/servo90';\">Turn servo to 90 degrees</button>\r\n";
        response += "</html>\n";
        if (request.indexOf("/servo90") != -1) {
          servo.write(90); // Set servo position to 90 degrees
          delay(1000);
        }
        client.print(response);
        break;
      }
    }
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
