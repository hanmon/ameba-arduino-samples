#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\BlinkLedUsingTimeFunc\\BlinkLedUsingTimeFunc.ino"
const int ledR=9;
unsigned long lastTime=0,interval=1000;
bool ledState=LOW;
#line 4 "d:\\project\\ameba-arduino-samples\\BlinkLedUsingTimeFunc\\BlinkLedUsingTimeFunc.ino"
void setup();
#line 11 "d:\\project\\ameba-arduino-samples\\BlinkLedUsingTimeFunc\\BlinkLedUsingTimeFunc.ino"
void loop();
#line 4 "d:\\project\\ameba-arduino-samples\\BlinkLedUsingTimeFunc\\BlinkLedUsingTimeFunc.ino"
void setup()
{
    Serial.begin(115200);
    Serial.print("Example:BlinkLedUsingTimeFunc");
	pinMode(ledR,OUTPUT);
}

void loop()
{
	if(millis()-lastTime>interval){
        ledState=!ledState;
        digitalWrite(ledR,ledState);
        lastTime=millis();    
    }
}

