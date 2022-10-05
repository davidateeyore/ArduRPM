

// Lathe-RPM-CounterV3.ino
// dt 15DEC2021
// more stuff dt 02DEC2021
// more changes dt 10DEC2021
// input from slotted disc/optointerrupter mounted
// on MiniLathe tailstock spindle
// to dt ArduPSU PCB driving 8x2 OLED display
// uses atMEGA328 (UNO like)
// some code based on: www.instructables.com/id/Arduino-Based-Optical-Tachometer/  
//
// The interrupt arrangement do not appear to work with my test setup
// so I will try a different counting approach..
// =======================
// I/O Pin definitions    
// =======================
#include <Adafruit_CharacterOLED.h>
#include <Wire.h>
#include <FreqMeasure.h>
#include <stdlib.h>

// #define ledPin 13

const byte ledPin = 13;
int sensorPin = 4;  // this library requires pin "D8" for UNO, bur we are using D8,
// so "D4 (Pin 6)" will have to replace D8 Pin 14....
// initialize the library with the OLED hardware 
// version OLED_Vx and numbers of the interface pins. 
// OLED_V1 = older, OLED_V2 = newer. If 2 doesn't work try 1 ;)
// Adafruit_CharacterOLED CounterOLED(OLED_V2, 6, 7, 8, 9, 10, 11, 12); // testing
Adafruit_CharacterOLED CounterOLED(OLED_V2, 12, 11, 10, 4, 7, 6, 5); // using PCB
// pin D8 changed to pin D4
// rs, rw, enable, d4, d5, d6, d7
//**********************************
//
//**********************************
void setup() {
  // put your setup code here, to run once:
  // initialise OLED
  // rpm = 1234; // just a display test value..
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  //pinMode(sensorPin, INPUT);
  CounterOLED.begin(8, 2);
  CounterOLED.clear(); 
  CounterOLED.print("LatheRPM");
  CounterOLED.setCursor(0,1);  // line 2 
  CounterOLED.print("dtV0.58");
  delay(2000); // so that I can see the init and version!
  CounterOLED.clear(); // flush screen..
  // setup counter
  FreqMeasure.begin();
  // 3 blinks to make sure arduino is working.. 
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);  
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW); 
  delay(100); 
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);  
  // 
}

double sum=0;
int count=0;

void loop() {
  // put your main code here, to run repeatedly:
  // code for reading optointerrupter and RPM display
  //

  CounterOLED.setCursor(0,0);  // line 1
  CounterOLED.print("My Lathe");
  CounterOLED.setCursor(0,1);  // line 2  
  CounterOLED.print("RPM=");
  //delay(200);
  
  //delay(200);
  CounterOLED.setCursor(4,1);
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      CounterOLED.setCursor(4,1);
      int rpm = ((frequency * 60)/10);  // Hz to RPM divided by 10 - opto 
      // produces 10 pulses per revolution
      CounterOLED.print(rpm);
      
      CounterOLED.print("    "); // flush previous reading..
      sum = 0;
      count = 0;
    }
  }
  // Update RPM every second
  //delay(1000);
  //rpm = int(pulseCount/10); // 10 slots on disc wheel..
  // now display rpm!
  //CounterOLED.print(rpm);
  //delay(1000);  // just to see what changes..
  //
  //
}
