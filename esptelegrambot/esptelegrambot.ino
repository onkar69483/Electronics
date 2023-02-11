#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "Galaxy";
const char* password = "prem3562951413";

#define BOTtoken "5651849401:AAEdhpyEUdbYx8Wx9pxgJvFJBHEIwQAq2JA"
#define CHAT_ID "1093493235"

int button = 5;
int led = 4;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT); 
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    bot.sendMessage(CHAT_ID, ".", "");
    delay(500);
    a++;
  }

  bot.sendMessage(CHAT_ID, "Wifi Connected", "");
  bot.sendMessage(CHAT_ID, "System started", "");

}

void loop() {
    int state = digitalRead(button);    
  if (state == 0){
    digitalWrite(led, HIGH);
    
  bot.sendMessage(CHAT_ID, "Emergency Detected!", "");
  }
  else{
    digitalWrite(led, LOW);
  }
}
