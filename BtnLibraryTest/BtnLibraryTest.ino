#include "Button.h"
Button button(3);
const int ledR=9;
bool ledState=LOW;
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
