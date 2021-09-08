#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
#include <LiquidCrystal.h>
#include <RotaryEncoder.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 0.5

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 32

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);


#define PIN_IN1 12
#define PIN_IN2 11

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::FOUR3);

//Parameters (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// defines analog pins numbers
int analogPin1 = 14;
int analogPin2 = 15;

int pos = 0;
int newPos=0;

float val = 0; 

int valout;
 long i=0;
 int initial=0;
 int direct=0;
 int prevdirect=0;

void setup() {
  #if FASTADC
 // set prescale to 16
 sbi(ADCSRA,ADPS2) ;
 cbi(ADCSRA,ADPS1) ;
 cbi(ADCSRA,ADPS0) ;
#endif
  
stepper.begin(RPM, MICROSTEPS);
 lcd.begin(16,2); // Initializes the 16x2 LCD screen
  Serial.begin(9600);  
  
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
  
  while (val>600 && newPos!=0)
  
  {
   if(direct==0){
    lcd.clear();
    lcd.print("FORWARD"); 
    direct++;
    //digitalWrite(dirPin,LOW);
   }
   val = analogRead(analogPin2);
   //Advance a step
  // digitalWrite(stepPin,HIGH);
   //delayMicroseconds(1);
   //delayMicroseconds(floor(2*(abs(val/100*5-25)/25)));
   //digitalWrite(stepPin,LOW);
   stepper.move(-1*MICROSTEPS);


   
   //Serial.println(val/100*5);  
   prevdirect=0;
   
    
  }
  direct=0; 

   while (val<400 && newPos!=0)
  
  {
   if(direct==0){
    lcd.clear();
    lcd.print("REVERSE"); 
    direct++;
    //digitalWrite(dirPin,HIGH);
   }
  
   //Advance a step
   //digitalWrite(stepPin,HIGH);
   //delayMicroseconds(1);
   //delayMicroseconds(floor(2*(abs(val/100*5-25)/25)));
  // digitalWrite(stepPin,LOW);
   stepper.move(MICROSTEPS);
   val = analogRead(analogPin2);
   //Serial.println(val/100*5);  
   prevdirect=0;
  // steps++;
    
  }
  direct=0;
  encoder.tick();

  newPos = encoder.getPosition();
  if (pos != newPos) {
    if(newPos==0){
      
    }else{
      stepper.begin(-50*newPos, MICROSTEPS);
    }
    
    lcd.clear();
    lcd.print(-newPos);
    pos = newPos;
  } // if
// loop ()
}
