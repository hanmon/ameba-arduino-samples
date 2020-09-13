# 1 "/home/bruce/win-data/project/ameba-arduino-samples/exercises/DoorSecuritySystem/DoorSecuritySystem.ino"
const int reedPin=4,activeBuzzerPin=5;
bool lastState;
void setup()
{
    pinMode(reedPin,0x00);
    pinMode(activeBuzzerPin,0x01);
    Serial.begin(115200);
    lastState=digitalRead(reedPin);
}

void loop()
{
    switch(checkReedRelayState()){
        case 1:
            Serial.println("Door Opened");
            digitalWrite(activeBuzzerPin,0x1);
            break;
        case 2:
            Serial.println("Door Closed");
            digitalWrite(activeBuzzerPin,0x0);
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
