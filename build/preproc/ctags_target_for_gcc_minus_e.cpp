# 1 "/home/bruce/win-data/project/ameba-arduino-samples/ReedRelay/ReedRelay.ino"
const int reedPin=4;
static bool lastState;
void setup()
{
    pinMode(reedPin,0x00);
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
