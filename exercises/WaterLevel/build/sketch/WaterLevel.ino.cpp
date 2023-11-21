#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\exercises\\WaterLevel\\WaterLevel.ino"
const int analogPin = A2, redPin = 9,threshold=350;
unsigned long lastTime = 0;
#line 3 "d:\\project\\ameba-arduino-samples\\exercises\\WaterLevel\\WaterLevel.ino"
void setup();
#line 9 "d:\\project\\ameba-arduino-samples\\exercises\\WaterLevel\\WaterLevel.ino"
void loop();
#line 3 "d:\\project\\ameba-arduino-samples\\exercises\\WaterLevel\\WaterLevel.ino"
void setup()
{
    Serial.begin(115200);
    pinMode(redPin, OUTPUT);
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
            digitalWrite(redPin, LOW);
        }
        else
        {
            Serial.println("Value < Threshold");
             //Turn off the led
            digitalWrite(redPin, HIGH);
        }
        lastTime=millis();
    }
}

