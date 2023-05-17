#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


const char* ssid = "";
const char* password = "";


#define BOTtoken ""
#define CHAT_ID ""


X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int button = 5;
int led = 4;

void setup()
{
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      
  client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    a++;
  }
  
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT); 

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "Wifi Connected!", "");
  bot.sendMessage(CHAT_ID, "System has Started!!", "");

}
void loop()
{

  int state = digitalRead(button);    
  if (state == 0){
     bot.sendMessage(CHAT_ID, "Blind Stick Emergency Detected!", "");
  }
  else{
    digitalWrite(led, LOW);
  }

}
