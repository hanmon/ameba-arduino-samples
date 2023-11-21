#include "SetRgbLed.h"
SetRgbLed rgb(COMMON_ANODE,9,10,11);
void setup(){
  
}

void loop(){
  rgb.showSevenColors();
}
