#ifndef SetRgbLed_h
#define SetRgbLed_h
#include <Arduino.h>
#define  COMMON_ANODE 1
#define  COMMON_CATHODE 2
enum COLORS {RED,ORANGE,YELLOW,GREEN,BLUE,INDIGO,PURPLE};
class SetRgbLed
{
public:
    //member variables

    unsigned long colorMap[7] = {0xFF0000, 0xFF9800, 0xFFEB3B, 0x00FF00, 0xFF, 0x303F9F, 0x9C27B0};
    char *colorName[7] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "PURPLE"};
    // Constructor
    SetRgbLed(int ledType, int redPin, int greenPin, int bluePin);
    // functions
    // void begin();
    void setColor(int red, int green, int blue);
    void setColor(int color);
    void showSevenColors();
    //
private:
    int _ledType;
    int _redPin;
    int _greenPin;
    int _bluePin;
};

#endif