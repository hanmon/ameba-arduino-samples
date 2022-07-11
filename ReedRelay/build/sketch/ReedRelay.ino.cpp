#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\ReedRelay\\ReedRelay.ino"
const int reedPin=3,ledPin=9,buzzerPin=4;
static bool lastState;
#line 3 "d:\\project\\ameba-arduino-samples\\ReedRelay\\ReedRelay.ino"
void setup();
#line 13 "d:\\project\\ameba-arduino-samples\\ReedRelay\\ReedRelay.ino"
void loop();
#line 29 "d:\\project\\ameba-arduino-samples\\ReedRelay\\ReedRelay.ino"
int checkReedRelayState();
#line 3 "d:\\project\\ameba-arduino-samples\\ReedRelay\\ReedRelay.ino"
void setup()
{
    pinMode(reedPin,INPUT);
    pinMode(ledPin,OUTPUT);
    pinMode(buzzerPin,OUTPUT);
    Serial.begin(115200);
    Serial.print("Example:ReedRelay");
    lastState=digitalRead(reedPin);
}

void loop()
{
    switch(checkReedRelayState()){
        case 1:
            Serial.println("Door Opened");
            digitalWrite(ledPin,HIGH);
            digitalWrite(buzzerPin,HIGH);
            break;
        case 2:
            Serial.println("Door Closed");
            digitalWrite(ledPin,LOW);
            digitalWrite(buzzerPin,LOW);
            break;
    }
}

int checkReedRelayState(){
    if(digitalRead(reedPin)!=lastState){
        delay(20);
        if(digitalRead(reedPin)!=lastState){
            lastState=digitalRead(reedPin);
            return lastState?1:2;
        }
    }
    else 
        return 0;
}

