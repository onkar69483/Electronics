#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid     = "";
const char* password = "";

WiFiServer server(80);

int LDR1 = A0; //for ldr sensors
int count = 0;


void setup() {
  pinMode(LDR1, INPUT);  //LDR Pins
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Return the response
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: text/html\r\n";
  response += "Connection: close\r\n";
  response += "Refresh: 1\r\n"; // Refresh the page every second
  response += "\r\n";
  response += "<!DOCTYPE HTML>\r\n";
  response += "<html><body>\r\n";
  response += "<h1>Laser Tag Web Server</h1>\r\n";
  response += "<p>Count: <span id=\"counter\">" + String(count) + "</span><p>\r\n";
  response += "<script>setInterval(function() { updateCounter(); }, 1000); function updateCounter() { var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (this.readyState == 4 && this.status == 200) { document.getElementById(\"counter\").innerHTML = this.responseText; } }; xhttp.open(\"GET\", \"/counter\", true); xhttp.send(); }</script>\r\n";
  response += "</body></html>\r\n";

  client.print(response);
  delay(1);
  Serial.println("Client disonnected");
int ldr1Value = analogRead(LDR1);
delay(1000);
Serial.println("LDR value: "+String(ldr1Value));
if (ldr1Value > 900 ) {  //change the intensity '900' accordingly
    count++;
    Serial.println("Count: " + String(count));
  }

    
}
