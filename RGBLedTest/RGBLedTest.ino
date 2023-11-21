/*
   A simple RGB Led Test. There are two overloading functions called "setColor"
   By Bruce Chiu
*/
// for lighting control
#define COMMON_ANODE
const int redPin = 9;
const int bluePin = 10;
const int greenPin = 11;
// Defining Color Value and Name
unsigned long colorMap[] = {0xFF0000, 0xFF9800, 0xFFEB3B, 0x00FF00, 0xFF, 0x303F9F, 0x9C27B0,0x000000,0xFFFFFF,0xF06292};
char *colorName[] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "PURPLE","BLACK","WHITE","PINK"};
enum color
{
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  INDIGO,
  PURPLE,
  BLACK,
  WHITE,
  PINK
};

void setup()
{
  Serial.begin(115200);
  //blink RED、GREEN、BLUE once
  setColor(RED);
  delay(1000);
  setColor(BLACK);
  delay(1000);
  setColor(GREEN);
  delay(1000);
  setColor(BLACK);
  delay(1000);
  setColor(BLUE);
  delay(1000);
  setColor(BLACK);
  delay(1000);
  setColor(PINK);
  delay(1000);
  setColor(BLACK);
  delay(1000);
}

void loop()
{
  showSevenColors();
}

void showSevenColors()
{
  int red, green, blue;
  char strBuffer[30];
  for (int i = 0; i < sizeof(colorMap) / sizeof(unsigned long); i++)
  {
    red = (colorMap[i] & 0xFF0000) >> 16;
    green = (colorMap[i] & 0xFF00) >> 8;
    blue = colorMap[i] & 0xFF;
    // set RGB Color to RGB Led
    // setColor(red,green,blue);
    // set RGB Color to RGB Led by another function
    setColor(i);
    Serial.println(colorName[i]);
    sprintf(strBuffer, "R:%d,G:%d,B:%d", red, green, blue);
    Serial.println(strBuffer);
    delay(1000);
  }
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setColor(int idx)
{
  int red = (colorMap[idx] & 0xFF0000) >> 16;
  int green = (colorMap[idx] & 0xFF00) >> 8;
  int blue = colorMap[idx] & 0xFF;
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
