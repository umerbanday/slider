#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
#include <LiquidCrystal.h>

//Parameters (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// defines pins numbers
int analogPin1 = 14;
int analogPin2 = 15;

float val = 0; 
float val1=0;
const int stepPin = 9; 
const int dirPin = 8; 
int valout;
 long i=0;
 int initial=0;
 int direct=0;
 int prevdirect=0;
 int steps=0;
void setup() {
  #if FASTADC
 // set prescale to 16
 sbi(ADCSRA,ADPS2) ;
 cbi(ADCSRA,ADPS1) ;
 cbi(ADCSRA,ADPS0) ;
#endif
  
 lcd.begin(16,2); // Initializes the 16x2 LCD screen
  Serial.begin(9600);  
  
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
 // pinMode(valpin,OUTPUT);
  digitalWrite(dirPin,LOW);
}
void loop() {
  if(initial==0){
    lcd.print("Starting Slider");
    delay(2000);
    initial++;
  }

  if(prevdirect==0){
    lcd.clear();
    lcd.print("STOPPED");
    prevdirect++; 
  }
  
  val = analogRead(analogPin2);  
  
  while (val>600)
  
  {
   if(direct==0){
    lcd.clear();
    lcd.print("FORWARD"); 
    direct++;
    digitalWrite(dirPin,LOW);
   }
   val = analogRead(analogPin2);
   //Advance a step
   digitalWrite(stepPin,HIGH);
   delayMicroseconds(1);
   //delayMicroseconds(floor(2*(abs(val/100*5-25)/25)));
   digitalWrite(stepPin,LOW);
   
   //Serial.println(val/100*5);  
   prevdirect=0;
   
    
  }
  steps=0;
  direct=0; 

   while (val<400)
  
  {
   if(direct==0){
    lcd.clear();
    lcd.print("REVERSE"); 
    direct++;
    digitalWrite(dirPin,HIGH);
   }
  
   //Advance a step
   digitalWrite(stepPin,HIGH);
   delayMicroseconds(1);
   //delayMicroseconds(floor(2*(abs(val/100*5-25)/25)));
   digitalWrite(stepPin,LOW);
   val = analogRead(analogPin2);
   //Serial.println(val/100*5);  
   prevdirect=0;
  // steps++;
    
  }
  steps=0;
  direct=0;
  Serial.println(val);
}
