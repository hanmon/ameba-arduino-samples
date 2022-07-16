# 1 "d:\\project\\ameba-arduino-samples\\exercises\\ASCiiLookup\\ASCiiLookup.ino"


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
        Serial.print(c, 10);
        Serial.print(",HEX:");
        Serial.print(c, 16);
        Serial.print(",OCT:");
        Serial.print(c, 8);
        Serial.print(",BIN:");
        Serial.println(c, 2);
    }
}
