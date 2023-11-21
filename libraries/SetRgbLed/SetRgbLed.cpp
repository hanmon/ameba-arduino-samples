#include "SetRgbLed.h"

SetRgbLed::SetRgbLed(int ledType, int redPin, int greenPin, int bluePin)
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    Serial.begin(115200);
    _ledType = ledType;
    _redPin=redPin;
    _greenPin=greenPin;
    _bluePin=bluePin;
}

// void SetRgbLed::begin(){

// }

void SetRgbLed::setColor(int red, int green, int blue)
{
    if (_ledType == COMMON_ANODE)
    {
        red = 255 - red;
        green = 255 - green;
        blue = 255 - blue;
    }
    analogWrite(_redPin, red);
    analogWrite(_greenPin, green);
    analogWrite(_bluePin, blue);
}

void SetRgbLed::setColor(int color)
{
    int red = (colorMap[color] & 0xFF0000) >> 16;
    int green = (colorMap[color] & 0xFF00) >> 8;
    int blue = colorMap[color] & 0xFF;
    if (_ledType == COMMON_ANODE)
    {
        red = 255 - red;
        green = 255 - green;
        blue = 255 - blue;
    }
    analogWrite(_redPin, red);
    analogWrite(_greenPin, green);
    analogWrite(_bluePin, blue);
    //Serial.print("Showing ");
    //Serial.print(colorName[color]);
    //Serial.println("color");
}

void SetRgbLed::showSevenColors()
{
    int red, green, blue;
    char strBuff[30];
    for (int i = 0; i < sizeof(colorMap) / sizeof(unsigned long); i++)
    {
        red = (colorMap[i] & 0xFF0000) >> 16;
        green = (colorMap[i] & 0xFF00) >> 8;
        blue = colorMap[i] & 0xFF;
        sprintf(strBuff,"R,G,B:%d,%d,%d",red,green,blue);
        //Serial.println(strBuff);
        //Serial.println(colorName[i]);
        setColor(red, green, blue);
        delay(1000);
    }
}