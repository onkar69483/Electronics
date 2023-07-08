#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid="ssid";
const char* password="pass";

WiFiServer server(80); //initializing wifi server at port 80

Servo servo1,servo2,servo3; //3 servo's we will be using for dispensing mechanism

const int switch1 = 14, switch2 = 12, switch3 = 13; // 3 switches which use to control 3 servo's indivisually 

void setup() {
  // put your setup code here, to run once:

servo1.attach(5); //servo
  pinMode(switch1, INPUT_PULLUP); //switch set as input_pullup
servo2.attach(4); 
  pinMode(switch2, INPUT_PULLUP); 
servo3.attach(0); 
  pinMode(switch3, INPUT_PULLUP); 

  servo1.write(0);
   servo2.write(0);
    servo3.write(0);

Serial.begin(115200);
Serial.print("Connecting to.");
Serial.println(ssid);

WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);

while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print("..");
  }
Serial.println("Connected to Wifi!");
Serial.println(WiFi.localIP());
 server.begin(); // starting the server
 delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client; //can send http request to this wifiClient
client=server.available();

int val1 = digitalRead(switch1);//reading values from the switches to initializing dispensing(servo rotation)
int val2 = digitalRead(switch2);
int val3 = digitalRead(switch3);

if(val1 == 0){
  servo1.write(180);
  Serial.println("Tablet1_Dispensed!");
  delay(2000);
  servo1.write(0);
}
if(val2 == 0){
  servo2.write(180);
  Serial.println("Tablet2_Dispensed!");
  delay(2000);
  servo2.write(0);
}
if(val3 == 0){
  servo3.write(180);
  Serial.println("Tablet3_Dispensed!");
  delay(2000);
  servo3.write(0);
}
else{
  servo1.write(0);
   servo2.write(0);
    servo3.write(0);
}

if (client ==1){  //recieving request from website
  String request=client.readStringUntil('\n'); //reading request
  client.flush();
  Serial.println(request);
  if (request.indexOf("connected") != -1){
     Serial.println("Tkinter Interface Initiated!");
     client.println("HTTP/1.1 200 OK"); 
  }
  else if (request.indexOf("Tablet1") != -1){  //if request is Tablet1 or from switch 1, Tablet1 will dispense
     servo1.write(180);
    delay(2000);
    servo1.write(0);
      client.println("HTTP/1.1 200 OK"); //OK! response to the client
    Serial.println("Tablet1 Dispensed!");
    }
  else if (request.indexOf("Tablet2") != -1){
     servo2.write(180);
    delay(2000);
    servo2.write(0);
      client.println("HTTP/1.1 200 OK");
    Serial.println("Tablet2 Dispensed!");
    }
  else if (request.indexOf("Tablet3") != -1){
      servo3.write(180);
    delay(2000);
    servo3.write(0);
    client.println("HTTP/1.1 200 OK");
    Serial.println("Tablet3 Dispensed!");
    }

    Serial.print("Client Disconnected");
    Serial.println("===========================================================");
  Serial.println("                              ");
  delay(1000);
}
}
