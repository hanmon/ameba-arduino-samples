#include <Arduino.h>
#line 1 "/home/bruce/win-data/project/ameba-arduino-samples/exercises/DoorSecuritySystem/DoorSecuritySystem.ino"
const int reedPin=4,activeBuzzerPin=5;
bool lastState;
#line 3 "/home/bruce/win-data/project/ameba-arduino-samples/exercises/DoorSecuritySystem/DoorSecuritySystem.ino"
void setup();
#line 11 "/home/bruce/win-data/project/ameba-arduino-samples/exercises/DoorSecuritySystem/DoorSecuritySystem.ino"
void loop();
#line 25 "/home/bruce/win-data/project/ameba-arduino-samples/exercises/DoorSecuritySystem/DoorSecuritySystem.ino"
int checkReedRelayState();
#line 3 "/home/bruce/win-data/project/ameba-arduino-samples/exercises/DoorSecuritySystem/DoorSecuritySystem.ino"
void setup()
{
    pinMode(reedPin,INPUT);
    pinMode(activeBuzzerPin,OUTPUT);
    Serial.begin(115200);
    lastState=digitalRead(reedPin);
}

void loop()
{
    switch(checkReedRelayState()){
        case 1:
            Serial.println("Door Opened");
            digitalWrite(activeBuzzerPin,HIGH);
            break;
        case 2:
            Serial.println("Door Closed");
            digitalWrite(activeBuzzerPin,LOW);
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

