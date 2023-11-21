#include "SetRgbLed.h"
SetRgbLed rgb(COMMON_ANODE,9,10,11);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Example:SetRgbLed");
}

void loop() {
  // put your main code here, to run repeatedly:
  rgb.showSevenColors();
}
