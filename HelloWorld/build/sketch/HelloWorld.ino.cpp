#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\HelloWorld\\HelloWorld.ino"
const int ledR=9;
#line 2 "d:\\project\\ameba-arduino-samples\\HelloWorld\\HelloWorld.ino"
void setup();
#line 9 "d:\\project\\ameba-arduino-samples\\HelloWorld\\HelloWorld.ino"
void loop();
#line 2 "d:\\project\\ameba-arduino-samples\\HelloWorld\\HelloWorld.ino"
void setup(){
    pinMode(ledR,OUTPUT);
    Serial.begin(115200);
    Serial.print("Hello World example for ameba arduino");
    
}

void loop(){
    digitalWrite(ledR,HIGH);
    delay(500);
    digitalWrite(ledR,LOW);
    delay(500);
}
