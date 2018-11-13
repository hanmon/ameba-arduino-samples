/*
   Measuring ambient light by light dependent resistor module connected with ameba arduino and printing on I2C LCD
   Connecting A0 to ameba pin A0
   Connecting DO to ameba pin D2
   By Bruce Chiu
*/
//including I2C LCD related libraries
// LCM1602 I2C LCD
#include <Wire.h>   //Include I2C Library
#include <LiquidCrystal_I2C.h>  //Include I2C LCD Library
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int ldrPin = A0;
const int doPin = 18;
int analogValue = 0, prevAnalogValue = 0;
//for lighting control
#define COMMON_ANODE
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
//enum colors {RED = 9, GREEN, BLUE, OFF};
unsigned long colorMap[] = {0xF44336, 0xFF9800, 0xFFEB3B, 0x4CAF50, 0x29B6F6, 0x303F9F, 0x9C27B0};
char* colorName[] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "PURPLE"};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //initializing I2C LCD
  lcd.begin(16, 2);
  //set doPin as input
  pinMode(doPin, INPUT);
  //printing welcom message
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  lcd.setCursor(0, 1);
  lcd.print("I'm Ameba");
  delay(3000);
}

void loop() {
  showSevenColors();
  //  setColor(0xFF,0,0); //R
  //  delay(2000);
  //  setColor(0,0xFF,0); //G
  //  delay(2000);
  //  setColor(0,0,0xFF); //B
  //  delay(2000);
}

void showSevenColors() {
  int red, green, blue;
  for (int i = 0; i < sizeof(colorMap) / sizeof(unsigned long); i++) {
    red = (colorMap[i] & 0xFF0000) >> 16;
    green = (colorMap[i] & 0xFF00) >> 8;
    blue = colorMap[i] & 0xFF;
    Serial.println("R,G,B" + String(red) + "," + String(green) + "," + String(blue));
    setColor(red, green, blue);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Color:");
    lcd.print(colorName[i]);
    lcd.setCursor(0, 1);
    delay(1000);
  }
}




void setColor(int red, int green, int blue) {
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

//void setColor(colors c) {
//  switch (c) {
//    case RED:
//      analogWrite(redPin, 0);
//      analogWrite(greenPin, 255);
//      analogWrite(bluePin, 255);
//      break;
//    case GREEN:
//      analogWrite(redPin, 255);
//      analogWrite(greenPin, 0);
//      analogWrite(bluePin, 255);
//      break;
//    case BLUE:
//      analogWrite(redPin, 255);
//      analogWrite(greenPin, 255);
//      analogWrite(bluePin, 0);
//      break;
//    default:
//      analogWrite(redPin, 255);
//      analogWrite(greenPin, 255);
//      analogWrite(bluePin, 255);
//      break;
//  }
//}
