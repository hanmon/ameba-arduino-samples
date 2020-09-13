#include <Arduino.h>
#line 1 "/home/bruce/win-data/project/ameba-arduino-samples/ReedRelay/ReedRelay.ino"
const int reedPin=4;
static bool lastState;
#line 3 "/home/bruce/win-data/project/ameba-arduino-samples/ReedRelay/ReedRelay.ino"
void setup();
#line 10 "/home/bruce/win-data/project/ameba-arduino-samples/ReedRelay/ReedRelay.ino"
void loop();
#line 22 "/home/bruce/win-data/project/ameba-arduino-samples/ReedRelay/ReedRelay.ino"
int checkReedRelayState();
#line 3 "/home/bruce/win-data/project/ameba-arduino-samples/ReedRelay/ReedRelay.ino"
void setup()
{
    pinMode(reedPin,INPUT);
    Serial.begin(115200);
    lastState=digitalRead(reedPin);
}

void loop()
{
    switch(checkReedRelayState()){
        case 1:
            Serial.println("Door Opened");
            break;
        case 2:
            Serial.println("Door Closed");
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

