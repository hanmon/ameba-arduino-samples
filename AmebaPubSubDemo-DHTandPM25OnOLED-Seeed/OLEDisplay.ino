#include <Wire.h>
#include <SeeedOLED.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

//void initOLED(){
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  display.println("I'm Ameba!");
//  display.setTextColor(BLACK, WHITE); // 'inverted' text
//  display.println(3.141592);
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.print("0x"); display.println(0xDEADBEEF, HEX);
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//}

void initOLED(){
    Wire.begin();
    SeeedOled.init();
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("I'm Ameba!");
    SeeedOled.setTextXY(1,0);
    SeeedOled.putString("Temperature:");
    SeeedOled.setTextXY(2,0);
    SeeedOled.putString("Humidity:");
    SeeedOled.setTextXY(3,0);
    SeeedOled.putString("PM2.5:");
}
//
void clearOLED(){
  //for Adafruit library
  //display.clearDisplay();
  //for Seeed library
  SeeedOled.clearDisplay();
}

void serCursorToBegin(){
  //for Adafruit library
  //display.setCursor(0,0);
  //for Seeed library
  SeeedOled.setTextXY(0, 0);
}

void printOnOLED(char* content,unsigned char row){
  SeeedOled.setTextXY(row, 0);
  SeeedOled.putString(content);
  //SeeedOled.display();
}

//void printOnOLED(char* content){
//   //display.setCursor(row,0);
//   display.println(content);
//   display.display();
//  //  display.display();
// // delay(2000);
// 
//}
