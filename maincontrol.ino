#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
#include <LiquidCrystal.h>
//#include <Math.h>// includes the LiquidCrystal Library

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Parameters (rs, enable, d4, d5, d6, d7)

// defines pins numbers
int analogPin1 = 14;
int analogPin2 = 15;
//int valpin =3;// potentiometer wiper (middle terminal) connected to analog pin 3
// outside leads to ground and +5V

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
/*
 while((val/100*5>20)&&(val/100*5<30)){
    
 }
  

  if(prevdirect != direct){
    
    if(direct==1){

    //Serial.println("BLINK");
    
    lcd.clear();
    lcd.print("ADVANCE"); 
   
      
    }

    if(direct==0){

    lcd.clear();
    lcd.print("REVERSE"); 
      
    }

    if(direct==2){

    lcd.clear();
    lcd.print("STOPPED"); 
      
    }
  }

  //Serial.println(abs(val/100*5-25)/25);
  //Serial.println(floor(2*(abs(val/100*5-25)/25)));
  
 // Serial.println(direct);

   prevdirect=direct;  
  
  
  
  
  
  
  
  /*
  //analogWrite(valpin,0.8/5*255);
   digitalWrite(dirPin,LOW);
   lcd.clear();
   lcd.print("Forward");
  for(i=1;i<=8600;i++){
   val = analogRead(analogPin1);    
  // read the input pin
  Serial.println(val/100*5);
 
  digitalWrite(stepPin,HIGH);
  delay(2);
  //delay(1); 
   digitalWrite(stepPin,LOW);
  // delayMicroseconds(10);
    
 
  }

  delay(400);

  digitalWrite(dirPin,HIGH);
  lcd.clear();
  lcd.print("Reverse");

  for(i=1;i<=8600;i++){
  val1 = analogRead(analogPin2);    // read the input pin

  Serial.println(val1/100*5);
 
  digitalWrite(stepPin,HIGH);
   delay(2);
   digitalWrite(stepPin,LOW);
 // delayMicroseconds(50);
 
  }

  delay(400);
  
  
 
  
   
 //  for(i=1;i<=100;i++){
 
//  digitalWrite(stepPin,HIGH);
//  delayMicroseconds(3000); 
 //  digitalWrite(stepPin,LOW);
 //   delay(50);
 // }
//delay(1000);*/
}
