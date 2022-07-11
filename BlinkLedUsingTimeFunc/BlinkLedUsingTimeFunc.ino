const int ledR=9;
unsigned long lastTime=0,interval=1000;
bool ledState=LOW;
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
