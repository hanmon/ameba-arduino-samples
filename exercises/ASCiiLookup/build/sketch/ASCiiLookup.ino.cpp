#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\exercises\\ASCiiLookup\\ASCiiLookup.ino"


#line 3 "d:\\project\\ameba-arduino-samples\\exercises\\ASCiiLookup\\ASCiiLookup.ino"
void setup();
#line 9 "d:\\project\\ameba-arduino-samples\\exercises\\ASCiiLookup\\ASCiiLookup.ino"
void loop();
#line 29 "d:\\project\\ameba-arduino-samples\\exercises\\ASCiiLookup\\ASCiiLookup.ino"
void serialEvent();
#line 3 "d:\\project\\ameba-arduino-samples\\exercises\\ASCiiLookup\\ASCiiLookup.ino"
void setup()
{
    Serial.begin(115200);
    Serial.println("Exercise:ASCiiLookup");
}

void loop()
{
    // if (Serial.available() > 0)
    // {
    //     char c = Serial.read();
    //     if (c != 10)
    //     {
    //         Serial.print(c);
    //         Serial.print(",DEC:");
    //         Serial.print(c, DEC);
    //         Serial.print(",HEX:");
    //         Serial.print(c, HEX);
    //         Serial.print(",OCT:");
    //         Serial.print(c, OCT);
    //         Serial.print(",BIN:");
    //         Serial.println(c, BIN);
    //     }
    // }
}

void serialEvent()
{
    char c = Serial.read();
    if (c != 10)
    {
        Serial.print(c);
        Serial.print(",DEC:");
        Serial.print(c, DEC);
        Serial.print(",HEX:");
        Serial.print(c, HEX);
        Serial.print(",OCT:");
        Serial.print(c, OCT);
        Serial.print(",BIN:");
        Serial.println(c, BIN);
    }
}
