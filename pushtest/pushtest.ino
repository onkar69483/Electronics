#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Galaxy";
const char* password = "12345678";

ESP8266WebServer server(80);

const int buttonPin = 5;
int buttonState = LOW;

void handleRoot() {
  String color = "green";
  if (buttonState == HIGH) {
    color = "red";
  }

  String html = "<html><head><title>Button Color</title></head><body bgcolor=\"" + color + "\"><h1>Button Color</h1><p>The button color is currently " + color + ".</p></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  buttonState = digitalRead(buttonPin);

  server.handleClient();
}
