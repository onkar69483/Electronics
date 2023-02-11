#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


const char* ssid = "Galaxy";
const char* password = "prem3562951413";


#define BOTtoken "5651849401:AAEdhpyEUdbYx8Wx9pxgJvFJBHEIwQAq2JA"
#define CHAT_ID "1093493235"


X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int const trigPin = 4;
int const echoPin = 5;
int const buzzPin = 12;
const int LED1 = 13;


void setup() {
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    a++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  bot.sendMessage(CHAT_ID, "Wifi Connected", "");
  bot.sendMessage(CHAT_ID, "System started", "");
  
}
void loop(){
int duration, distance;
digitalWrite(trigPin, HIGH);
delay(1);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance <= 10 && distance >= 0) {
digitalWrite(buzzPin, HIGH);
digitalWrite(LED1, HIGH);
bot.sendMessage(CHAT_ID, "Alert! Motion detected!!", "");
} else {
digitalWrite(buzzPin, LOW);
digitalWrite(LED1, LOW);
bot.sendMessage(CHAT_ID, "No Motion detected!!", "");
}
delay(60);

}
