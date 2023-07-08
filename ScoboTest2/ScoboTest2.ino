
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <style>
      * {
      	font-family: "Arial";
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }
      .form-container {
      	text-align: center;
        max-width: 500px;
        margin: 20vh auto;
        padding: 25px;
        border: 1px solid rgba(0,0,0,0.1);
        background-color: #fff;
        border-radius: 7px;
        box-shadow: 0 3px 4px 0 rgba(0,0,0,0.1);
      }
      .title {
      	margin: 0 0 20px 0;
      }
      .form {	
        display: flex;
        flex-direction: column;
        gap: 13px
      }
      .input-field {
      	padding: 10px;
        border-radius: 6px;
        width: 100%;
        border: 1px solid rgba(0,0,0,0.3);
      }
      .form-label {
      	display: block;
        margin-bottom: 10px;
      }
      .gap {
				margin-right: 15px;
      }
      .time-input {
      	margin-top: 5px;
        border-radius: 2px;
        border: 1px solid rgba(0,0,0,0.4);
      }
      .submit-button {
      	padding: 10px;
        border-radius: 6px;
        background-color: #4BB543;
        border: none;
        color: #fff;
        cursor: pointer;
        font-size: 1em;
      }
      .submit-button:hover {
      	background-color: #27b01e;
      }
      @media (max-width: 600px) {
        .form-container {
          max-width: 80%; /* Reduce the max-width on smaller screens */
          margin: 20vh auto; /* Add a bit of margin to the sides */
        }
      }
    </style>
  </head>
<body>
  <div class="form-container">
    <h2 class="title">Patient Medicine Dispenser</h2>
  

<form action="/action_page">

  <div class="patient-name">
    <input type="text" name ="pname" placeholder="Enter Patient name"  required class="input-field">
  </div>

  <div class="medicine-list">
    <label for="medicineSelect" class="form-label">Medication:</label>
    <select id="medicineSelect" name="medicine" class="input-field">
      <option value="medicine 1">Medicine 1</option>
      <option value="medicine 2">Medicine 2</option>
      <option value="medicine 3">Medicine 3</option>
    </select>
  </div>
  <div class="time-select">
    <div class="form-label">Medication Time:</div>
    <input type="radio" name="medication-time" value="now" id="now" required>
    <label for="now" class="gap">Now</label>

    <input type="radio" name="medication-time" value="schedule" id="schedule" required>
    <label for="schedule">Schedule</label>
    <input type="time" class="time-input" name="time">
  </div>
    <input type="submit" value="Add Medicine" class="submit-button">
</form> 
</body>
</html>
)=====";

//SSID and Password of your WiFi router
const char* ssid = "ssid";
const char* password = "pass";

ESP8266WebServer server(80); //Server on port 80
Servo servo1,servo2,servo3; //3 servo's we will be using for dispensing mechanism
const int switch1 = 14, switch2 = 12, switch3 = 13; // 3 switches which use to control 3 servo's indivisually 

void hardware(String medicine){

if(medicine=="medicine 1"){
   servo1.write(90);
  Serial.println("Tablet1_Dispensed!\n");
  delay(2000);
  servo1.write(0);
}
if(medicine=="medicine 2"){
   servo2.write(90);
  Serial.println("Tablet2_Dispensed!\n");
  delay(2000);
  servo2.write(0);
}
if(medicine=="medicine 3"){
   servo3.write(90);
  Serial.println("Tablet3_Dispensed!\n");
  delay(2000);
  servo3.write(0);
}
}
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//===============================================================
// This routine is executed when you press submit
//===============================================================
void handleForm() {
 String medName = server.arg("medicine"); 
String patientName = server.arg("pname");
String medicationTime = server.arg("medication-time");
 Serial.print("Medicine Name: ");
 Serial.println(medName);
  Serial.print("Patient Name: ");
 Serial.println(patientName);
   Serial.print("Medication Time: ");
 Serial.println(medicationTime);

 hardware(medName);

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated-- Press Back Button");  //This Line Keeps It on Same Page

}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  servo1.attach(5); //servo
  pinMode(switch1, INPUT_PULLUP); //switch set as input_pullup
servo2.attach(4); 
  pinMode(switch2, INPUT_PULLUP); 
servo3.attach(0); 
  pinMode(switch3, INPUT_PULLUP); 

  servo1.write(0);
   servo2.write(0);
    servo3.write(0);

  Serial.begin(9600);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/action_page", handleForm); //form action is handled here

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  int val1 = digitalRead(switch1);//reading values from the switches to initializing dispensing(servo rotation)
int val2 = digitalRead(switch2);
int val3 = digitalRead(switch3);

if(val1==0){
   servo1.write(90);
  Serial.println("Tablet1 Dispensed!\n");
  delay(2000);
  servo1.write(0);
}
if(val2==0){
   servo2.write(90);
  Serial.println("Tablet2 Dispensed!\n");
  delay(2000);
  servo2.write(0);
}
if(val3==0){
   servo3.write(90);
  Serial.println("Tablet3 Dispensed!\n");
  delay(2000);
  servo3.write(0);
}

server.handleClient();          //Handle client requests

}