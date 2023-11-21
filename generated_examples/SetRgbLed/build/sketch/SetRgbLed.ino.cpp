#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\generated_examples\\SetRgbLed\\SetRgbLed.ino"
#include "SetRgbLed.h"
SetRgbLed rgb(COMMON_ANODE,9,10,11);
#line 3 "d:\\project\\ameba-arduino-samples\\generated_examples\\SetRgbLed\\SetRgbLed.ino"
void setup();
#line 8 "d:\\project\\ameba-arduino-samples\\generated_examples\\SetRgbLed\\SetRgbLed.ino"
void loop();
#line 3 "d:\\project\\ameba-arduino-samples\\generated_examples\\SetRgbLed\\SetRgbLed.ino"
void setup()
{
	Serial.println("SetRgbLed Library Test");
}

void loop()
{
    //showing seven colors of rainbow sequentially,including RED,ORANGE,YELLOW,GREEN,BLUE,INDIGO and PURPLE
	//rgb.showSevenColors();
    //showing three colors sequentially, with 1sec delay for each color
    rgb.setColor(RED);
    delay(1000);
    rgb.setColor(GREEN);
    delay(1000);
    rgb.setColor(BLUE);
    delay(1000);
}

