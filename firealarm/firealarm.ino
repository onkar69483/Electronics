int flamesensor = 8;
int buzzer =12 ;
int greenled = 6;
int flame = LOW ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(flamesensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(greenled, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
flame = digitalRead(flamesensor);


  if (flame == LOW) {
  Serial.println( " fire occured please be safe");
  digitalWrite(greenled,LOW);
  digitalWrite(buzzer, LOW);
  delay (100);
  }
  else{

  digitalWrite(greenled,HIGH);
  digitalWrite(buzzer, HIGH);
  delay (100);
  
  }
}
