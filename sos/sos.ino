int button = 5;
int led = 4;
void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT); 
}

void loop() {
  int state = digitalRead(button);    
  if (state == 0){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }

}
