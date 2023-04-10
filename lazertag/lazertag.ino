
int LDR1 = A0; //for ldr sensors
/*int LDR2 = A1;
int LDR3 = A2;
int LDR4 = A3;*/

int count = 4;
int Intensity = 25;

int A = 9; //for 7segment display
int B = 2;
int C = 3;
int D = 4;
int E = 5;
int F = 6;
int G = 7;
int P = 8;

/*int led1 = 18;
int led2 = 10;
int led3 = 11;
int led4 = 19;*/



void setup() 

{
Serial.begin(9600);
pinMode(LDR1, INPUT);  //LDR Pins
/*pinMode(LDR2, INPUT);
pinMode(LDR3, INPUT);
pinMode(LDR4, INPUT);


pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);

digitalWrite(led1, HIGH); 
digitalWrite(led2, HIGH); 
digitalWrite(led3, HIGH); 
digitalWrite(led4, HIGH); */



for(int pin = 2;pin<10;pin++){ // 7Segment display pins
  pinMode(pin,OUTPUT);
}
}

void zero(void){ //functions to print score on 7segment display
  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(A, LOW);
  digitalWrite(P, LOW);
}


void one(void){
 digitalWrite(A, HIGH);
 digitalWrite(B, LOW);
 digitalWrite(C, LOW);
 digitalWrite(D, HIGH);
 digitalWrite(E, HIGH);
 digitalWrite(F, HIGH);
 digitalWrite(G, HIGH);
  digitalWrite(P, LOW);
}
void two(void){
 digitalWrite(A, LOW);
 digitalWrite(B, LOW);
 digitalWrite(C, HIGH);
 digitalWrite(D, LOW);
 digitalWrite(E, LOW);
 digitalWrite(F, HIGH);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void three(void){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}

void four(void){
 digitalWrite(A, HIGH);
 digitalWrite(B, LOW);
 digitalWrite(C, LOW);
 digitalWrite(D, HIGH);
 digitalWrite(E, HIGH);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void five(void){
 digitalWrite(A, LOW);
 digitalWrite(B, HIGH);
 digitalWrite(C, LOW);
 digitalWrite(D, LOW);
 digitalWrite(E, HIGH);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void six(void){
 digitalWrite(A, LOW);
 digitalWrite(B, HIGH);
 digitalWrite(C, LOW);
 digitalWrite(D, LOW);
 digitalWrite(E, LOW);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void seven(void){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
 digitalWrite(D, HIGH);
 digitalWrite(E, HIGH);
 digitalWrite(F, HIGH);
 digitalWrite(G, HIGH);
  digitalWrite(P, LOW);
}


void eight(void){
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}
void nine(void){
 digitalWrite(A, LOW);
 digitalWrite(B, LOW);
 digitalWrite(C, LOW);
 digitalWrite(D, LOW);
 digitalWrite(E, HIGH);
 digitalWrite(F, LOW);
 digitalWrite(G, LOW);
  digitalWrite(P, LOW);
}

void loop() {

int LDR1Value = analogRead(LDR1);
/*int LDR2Value = analogRead(LDR2);
int LDR3Value = analogRead(LDR3);
int LDR4Value = analogRead(LDR4);*/


Serial.print("sensor = ");
Serial.println(LDR1Value);
/*Serial.println(LDR2Value);
Serial.println(LDR3Value);
Serial.println(LDR4Value);*/

 
if (LDR1Value >=Intensity/*|| LDR2Value >=Intensity || LDR3Value >=Intensity || LDR3Value >=Intensity*/){ // '700' is the intensity here, change it as required.
count--;
}

Serial.println("Count =");
Serial.println(count);  

 /*if (LDR1Value >Intensity ) { 
    digitalWrite(led1, LOW);  
  }
     if (LDR2Value > Intensity) { 
    digitalWrite(led2, LOW);     
  }
     if (LDR3Value > Intensity) { 
    digitalWrite(led3, LOW);   
  }
     if (LDR4Value > Intensity) { 
    digitalWrite(led4, LOW);   
  }*/
  

if (count == 0){ //Printing on 7 segment display
    zero();
    delay(250);
  }
  if (count == 1){
    one();
    delay(250);
  }
  if (count == 2){
    two();
    delay(250);
  }
  if (count == 3){
    three();
    delay(250);
  }
  if (count == 4){
    four();
    delay(250);
  }
}
