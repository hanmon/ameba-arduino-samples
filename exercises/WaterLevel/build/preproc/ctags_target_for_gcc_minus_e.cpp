# 1 "d:\\project\\ameba-arduino-samples\\exercises\\WaterLevel\\WaterLevel.ino"
const int analogPin = 3, redPin = 9,threshold=350;
unsigned long lastTime = 0;
void setup()
{
    Serial.begin(115200);
    pinMode(redPin, 0x01);
    Serial.println("Water Level Detector");
}
void loop()
{
    int val = analogRead(analogPin);
    if ((millis() - lastTime) > 2000)
    {
        Serial.print("Value:");
        Serial.println(val);
        if (val > threshold)
        {
            Serial.println("Value > Threshold");
            //Turn on the led
            digitalWrite(redPin, 0x0);
        }
        else
        {
            Serial.println("Value < Threshold");
             //Turn off the led
            digitalWrite(redPin, 0x1);
        }
        lastTime=millis();
    }
}
