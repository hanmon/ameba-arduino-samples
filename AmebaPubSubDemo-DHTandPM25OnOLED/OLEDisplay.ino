//#include <Wire.h>
//#include <SeeedOLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void initOLED(){
  lcd.begin(16, 2);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("I'm Ameba!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void drawBitmap(){
  display.drawBitmap(0,0,CHT_logo,128,64,1);
  display.display();
}


void setTextColor(){
  display.setTextColor(WHITE,BLACK);
}
//void initOLED(){
//    Wire.begin();
//    SeeedOled.init();
//    SeeedOled.clearDisplay();
//    SeeedOled.setTextXY(0,0);
//    SeeedOled.putString("I'm Ameba!");
//    SeeedOled.setTextXY(1,0);
//    SeeedOled.putString("Temperature:");
//    SeeedOled.setTextXY(2,0);
//    SeeedOled.putString("Humidity:");
//    SeeedOled.setTextXY(3,0);
//    SeeedOled.putString("PM2.5:");
//}
//
void clearOLED(){
  display.clearDisplay();
}

void serCursorToBegin(){
 display.setCursor(0,0);
}

void printOnOLED(char* content){
   //display.setCursor(row,0);
   display.println(content);
   display.display();
  //  display.display();
 // delay(2000);
 
}
