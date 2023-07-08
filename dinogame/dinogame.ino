#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Set up WiFi access credentials
const char* ssid = "Galaxy";
const char* password = "prem3562951413";

// Initialize web server on port 80
ESP8266WebServer server(80);

// Set up pins for push switches
const int leftSwitchPin = 16;
const int rightSwitchPin = 5;

// Set up variables for ball position and velocity
int ballX = 64;
int ballY = 32;
int ballVelocityX = -1;
int ballVelocityY = 1;

// Set up variables for paddle positions
int leftPaddleY = 24;
int rightPaddleY = 24;

void setup() {
  // Set up push switches as inputs
  pinMode(leftSwitchPin, INPUT_PULLUP);
  pinMode(rightSwitchPin, INPUT_PULLUP);

  // Set up WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Set up web server handlers
  server.on("/", handleRoot);
  server.on("/update", handleUpdate);

  // Start web server
  server.begin();
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}

void handleRoot() {
  // Send HTML page with embedded JavaScript for Pong game
  String html = "<html><head><title>ESP8266 Pong Game</title>";
  html += "<script>function update() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "document.getElementById('game').innerHTML = this.responseText;";
  html += "}};";
  html += "xhttp.open('GET', '/update', true);";
  html += "xhttp.send();}";
  html += "setInterval(update, 100);</script></head>";
  html += "<body><div id='game'></div></body></html>";
  server.send(200, "text/html", html);
}

void handleUpdate() {
  // Update ball position and check for collisions with paddles or walls
  ballX += ballVelocityX;
  ballY += ballVelocityY;
  if (ballX <= 0) {
    ballVelocityX = 1;
  }
  if (ballX >= 127) {
    ballVelocityX = -1;
  }
  if (ballY <= 0 || ballY >= 63) {
    ballVelocityY = -ballVelocityY;
  }
  if (ballX == 16 && ballY >= leftPaddleY && ballY <= leftPaddleY + 15) {
    ballVelocityX = 1;
  }
  if (ballX == 112 && ballY >= rightPaddleY && ballY <= rightPaddleY + 15) {
    ballVelocityX = -1;
  }

  // Check for button presses and update paddle positions
  if (digitalRead(leftSwitchPin) == HIGH && leftPaddleY > 0) {
    leftPaddleY--;
  }
  if (digitalRead(rightSwitchPin) == HIGH && rightPaddleY > 0) {
    rightPaddleY--;
  }
  if (digitalRead(leftSwitchPin) == LOW && leftPaddleY < 48) {
    leftPaddleY++;
  }
}
