int irsensor = 5;
int led = 4;
int irvalue = LOW ;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irsensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
irvalue = digitalRead(irsensor);

  if (irvalue == HIGH) {
  count++;
  digitalWrite(led,HIGH);
  delay (100);
  }
  else{
  digitalWrite(led,LOW);
  delay (100);
    }
}
