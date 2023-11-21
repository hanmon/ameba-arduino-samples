# 1 "d:\\project\\ameba-arduino-samples\\RGBLedTest\\RGBLedTest.ino"
/*

   A simple RGB Led Test

   By Bruce Chiu

*/
# 7 "d:\\project\\ameba-arduino-samples\\RGBLedTest\\RGBLedTest.ino"
//for lighting control

const int redPin = 9;
const int bluePin = 10;
const int greenPin = 11;
//Defining Color Value and Name
unsigned long colorMap[] = {0xFF0000, 0xFF9800, 0xFFEB3B, 0x00FF00, 0xFF, 0x303F9F, 0x9C27B0};
char* colorName[]={"RED","ORANGE","YELLOW","GREEN","BLUE","INDIGO","PURPLE"};

void setup() {
  Serial.begin(115200);
}

void loop() {
  showSevenColors();
}

void showSevenColors() {
  int red, green, blue;
  char strBuffer[30];
  for(int i=0;i<sizeof(colorMap)/sizeof(unsigned long);i++){
    red = (colorMap[i] & 0xFF0000) >> 16;
    green = (colorMap[i] & 0xFF00) >> 8;
    blue = colorMap[i] & 0xFF;
    Serial.println(colorName[i]);
    rtl_sprintf(strBuffer,"R:%d,G:%d,B:%d",red,green,blue);
    Serial.println(strBuffer);
    delay(1000);
  }
}


void setColor(int red, int green, int blue) {

  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
