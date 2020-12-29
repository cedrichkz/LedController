#include <IRremote.h>
const int recpin = 12;
IRrecv irrecv(recpin);
decode_results results;
unsigned long key_value = 0;
#define REDLED 7
#define KNOP 2

const int red = 10;
const int blue = 9;
const int green = 3;
const int fadespeed = 10;
volatile int buttonState = 0; //volatile = verandering niet te voorspellen

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(REDLED, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(KNOP, INPUT);
  attachInterrupt(0, pin_ISR, RISING);
  irrecv.enableIRIn(); //ir receiver aanzetten
  irrecv.blink13(true); //led 13 zal blinken als rec een signaal krijgt
  
}

int niveau = -1;
int aanremote = 1;

void blauw(){
  analogWrite(red, LOW);
  analogWrite(green, LOW);
  analogWrite(blue, 255);
}
void rood(){
  analogWrite(red, 255);
  analogWrite(green, LOW);
  analogWrite(blue, LOW);
}
void groen(){
  analogWrite(red, LOW);
  analogWrite(green, 255);
  analogWrite(blue, LOW);
}

void wit(){
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 255);
}

void aan(){
  analogWrite(red, 122);
  analogWrite(green, 122);
  analogWrite(blue, 122);
}

void ledsuit(){
  niveau = -1;
  aanremote = -1;
  digitalWrite(REDLED, LOW);
  analogWrite(red, LOW);
  analogWrite(green, LOW);
  analogWrite(blue, LOW);
}

void testleds(){
  digitalWrite(REDLED, HIGH);
    
  analogWrite(green, 255);
  analogWrite(red, 255);
  Serial.println("Gedurende 5 sec kleur ...");
  delay(5000);
    
  Serial.println("Nu geleidelijk ... incrementeren");
  for(int i = 0; i<255; i++){
     analogWrite(blue, i);
     delay(10);
  }
  Serial.println("Gedurende 5 sec ...");
  delay(5000);
  analogWrite(red, LOW);
}

void simpelefade(){
  Serial.println("Simpele Fade programma");
  int r,b,g;
  analogWrite(blue, 255);
  for(r=0;r<256;r++){
    analogWrite(red, r);
    delay(fadespeed);
  }
  Serial.println("Fade Gedaan");
}

void ledsfade(){
  Serial.println("Fade programma");
  int r,b,g;
  
  for(r=0;r<256;r++){
    analogWrite(red, r);
    delay(fadespeed);
  }

  for(b = 255; b>0;b--){
    analogWrite(blue,b);
    delay(fadespeed);
  }

  for(g=0;g<256;g++){
    analogWrite(green, g);
    delay(fadespeed);
  }

  for(r = 255; r>0;r--){
    analogWrite(red,r);
    delay(fadespeed);
  }

  for(b=0;b<256;b++){
    analogWrite(blue, b);
    delay(fadespeed);
  }

  for(g = 255; g>0;g--){
    analogWrite(green,g);
    delay(fadespeed);
  }
 
}


void loop() {
  //lees staat knop
    
    //als rec een code heeft gekregen zal 
    if(irrecv.decode(&results)){
        Serial.println("Code gekregen");
        if(results.value == 0XFFFFFFFF){
          results.value = key_value;
        }
        switch(results.value){
          case 0xF7C03F:
          Serial.println("KNOP AAN");
          wit();
          break;
          
          case 0xF740BF:
          Serial.println("KNOP UIT");
          ledsuit();
          break;
          
          case 0xF7E01F:
          Serial.println("WIT");
          wit();
          break;
          
          case 0xF7609F:
          Serial.println("BLAUW");
          blauw();
          break;
          
          case 0xF7A05F:
          Serial.println("GROEN");
          groen();
          break;
          
          case 0xF720DF:
          Serial.println("ROOD");
          rood();
          break;
        }
  
        key_value = results.value;
        irrecv.resume();   
    
  }
}

void pin_ISR(){

  buttonState = digitalRead(KNOP);
  
  //als knop ingedrukt is, wachten tot weer los. En Leds uitdoen of aan
  if(buttonState>0){
    niveau *= -1;
    aanremote *= -1;
  }
  while(buttonState>0){
    buttonState = digitalRead(KNOP);
  }

  
}
