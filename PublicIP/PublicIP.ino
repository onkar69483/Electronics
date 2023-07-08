#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <Servo.h>

const char* ssid = "ssid";
const char* password = "pass";

const char* serverName = "https://scobobot.pythonanywhere.com/get_info/";

unsigned long lastTime = 0;
unsigned long timerDelay = 500;

Servo servo1,servo2,servo3;
int servoPin1 = 5,servoPin2 = 4,servoPin3= 14;
int servoAngle = 180;

void setup() {
  Serial.begin(115200);

  servo1.attach(servoPin1);
  servo1.write(0);
  servo2.attach(servoPin2);
  servo2.write(0);
  servo3.attach(servoPin3);
  servo3.write(0);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      String response = httpGETRequest(serverName);
      Serial.println(response);

      JSONVar json = JSON.parse(response);
      if (JSON.typeof(json) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      JSONVar medicineValue = json["medicine"];
      if (JSON.typeof(medicineValue) == "number") {
        int intValue = int(medicineValue);
        Serial.print("Medicine value (int): ");
        Serial.println(intValue);


      } else if (JSON.typeof(medicineValue) == "string") {
        String strValue = String(medicineValue);
        Serial.print("Medicine value (string): ");
        Serial.println(strValue);
          if (strValue == "1") {
          servo1.write(servoAngle);
          delay(2000);
          servo1.write(0);
          Serial.println("Medicine 1 Dispensed!");
        }
                  if (strValue == "2") {
          servo2.write(servoAngle);
          delay(2000);
          servo2.write(0);
          Serial.println("Medicine 2 Dispensed!");
        }
                  if (strValue == "3") {
          servo3.write(servoAngle);
          delay(2000);
          servo3.write(0);
          Serial.println("Medicine 3 Dispensed!");
        }
      } else {
        Serial.println("Invalid medicine value!");
      }
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}


String httpGETRequest(const char* serverName) {
  WiFiClientSecure client;
  HTTPClient http;

  // Disable certificate verification (only for testing, not recommended for production)
  client.setInsecure();

  http.begin(client, serverName);

  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return payload;
}
