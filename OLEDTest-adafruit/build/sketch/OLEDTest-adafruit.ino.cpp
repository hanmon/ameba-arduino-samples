#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
//#include <Wire.h>
//#include <SeeedOLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "CHT_logo.h"
#include "LASS.h"
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#line 11 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
void initOLED();
#line 44 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
void clearOLED();
#line 48 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
void serCursorToBegin();
#line 52 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
void printOnOLED(char* content);
#line 60 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
void setup();
#line 74 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
void loop();
#line 11 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
void initOLED(){
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
void setup()
{
  initOLED();
  //init PM2.5 Sensor
//  initUART2();
  display.drawBitmap(0,0,CHT_logo,128,64,1);
  display.display();
  delay(5000);
  display.clearDisplay();
  display.drawBitmap(0,0,LASS,128,64,1);
  display.display();
  delay(5000);
}
int startnum=241;
void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0); 
//  for (int i = startnum; i < startnum+20; i++)  {
//    display.print((char)i); 
//  }
  display.print(startnum); 
//  display.print("start:"); 
//  display.println(startnum); 
//  display.print("end:"); 
//  display.println(startnum+20); 
  
  display.display();
  delay(5000);  //waits 5 seconds, change to longer if you need more time to view the display
  startnum = startnum + 20;  //increments the starting number for the next loop by 20
  
}

