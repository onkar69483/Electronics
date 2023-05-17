#include <SoftwareSerial.h>
SoftwareSerial espSerial(12, 13);  // RX, TX pins of the ESP01 module

const char* ssid = "";  // your network SSID (name)
const char* password = "";  // your network password

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  // Connect to Wi-Fi network
  sendCommand("AT+CWJAP=\""+String(ssid)+"\",\""+String(password)+"\"", "OK", 5000);
  Serial.println("Connected to Wi-Fi network");
  
  // Start the server
  sendCommand("AT+CWMODE=3", "OK", 1000);
  sendCommand("AT+CIPMUX=1", "OK", 1000);
  sendCommand("AT+CIPSERVER=1,80", "OK", 1000);
  Serial.println("Server started");
}

void loop() {
  if (espSerial.available()) {
    // Check for incoming data
    String data = espSerial.readStringUntil('\r\n');
    Serial.println(data);

    // Check if the client has sent a request
    if (data.indexOf("GET /") >= 0) {
      // Send response to client
      espSerial.println("HTTP/1.1 200 OK");
      espSerial.println("Content-Type: text/html");
      espSerial.println("");
      espSerial.println("<html><body><h1>Hi</h1></body></html>");
    }
  }
}

// Helper function to send AT commands and check the response
void sendCommand(String command, String expectedResponse, int timeout) {
  espSerial.println(command);
  delay(timeout);
  while (espSerial.available()) {
    String response = espSerial.readStringUntil('\r\n');
    if (response.indexOf(expectedResponse) >= 0) {
      return;
    }
  }
}
