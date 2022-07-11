# 1 "d:\\project\\ameba-arduino-samples\\ReedRelay\\ReedRelay.ino"
const int reedPin=3,ledPin=9,buzzerPin=4;
static bool lastState;
void setup()
{
    pinMode(reedPin,0x00);
    pinMode(ledPin,0x01);
    pinMode(buzzerPin,0x01);
    Serial.begin(115200);
    Serial.print("Example:ReedRelay");
    lastState=digitalRead(reedPin);
}

void loop()
{
    switch(checkReedRelayState()){
        case 1:
            Serial.println("Door Opened");
            digitalWrite(ledPin,0x1);
            digitalWrite(buzzerPin,0x1);
            break;
        case 2:
            Serial.println("Door Closed");
            digitalWrite(ledPin,0x0);
            digitalWrite(buzzerPin,0x0);
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
