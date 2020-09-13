#include "blinkLed.h"
const int ledPin=13;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  blinkLed(ledPin,FAST,5);
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkLed(ledPin,SLOW,1);  
}
