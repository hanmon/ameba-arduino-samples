# 1 "d:\\project\\ameba-arduino-samples\\BlinkLedUsingTimeFunc\\BlinkLedUsingTimeFunc.ino"
const int ledR=9;
unsigned long lastTime=0,interval=1000;
bool ledState=0x0;
void setup()
{
    Serial.begin(115200);
    Serial.print("Example:BlinkLedUsingTimeFunc");
 pinMode(ledR,0x01);
}

void loop()
{
 if(millis()-lastTime>interval){
        ledState=!ledState;
        digitalWrite(ledR,ledState);
        lastTime=millis();
    }
}
