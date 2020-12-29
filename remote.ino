#include <IRremote.h>
const int recpin = 12;
IRrecv irrecv(recpin);
decode_results results;
unsigned long key_value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn(); //ir receiver aanzetten
  irrecv.blink13(true); //led 13 zal blinken als rec een signaal krijgt
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("dede");

  //als rec een code heeft gekregen zal 
  if(irrecv.decode(&results)){
      Serial.println(results.value, HEX);
      if(results.value == 0XFFFFFFFF){
        results.value = key_value;
      }
      switch(results.value){
        case 0xF7C03F:
        Serial.println("AAN");
        break;
        case 0xF740BF:
        Serial.println("UIT");
        break;
        case 0xF7E01F:
        Serial.println("WIT");
        break;
        case 0xF7609F:
        Serial.println("BLAUW");
        break;
        case 0xF7A05F:
        Serial.println("GROEN");
        break;
        case 0xF720DF:
        Serial.println("ROOD");
        break;
      }

      key_value = results.value;
      irrecv.resume();
  }

}
