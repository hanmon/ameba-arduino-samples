#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\BtnLibraryTest\\BtnLibraryTest.ino"
#include "Button.h"
Button button(3);
const int ledR=9;
bool ledState=LOW;
#line 5 "d:\\project\\ameba-arduino-samples\\BtnLibraryTest\\BtnLibraryTest.ino"
void setup();
#line 12 "d:\\project\\ameba-arduino-samples\\BtnLibraryTest\\BtnLibraryTest.ino"
void loop();
#line 5 "d:\\project\\ameba-arduino-samples\\BtnLibraryTest\\BtnLibraryTest.ino"
void setup()
{
	button.begin();
    Serial.begin(115200);
    pinMode(ledR,OUTPUT);
}

void loop()
{
	if(button.pressed()){
        Serial.println("Button Pressed");
        ledState=!ledState;
        digitalWrite(ledR,ledState);
    }
        
}

