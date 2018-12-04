//#include <Wire.h>
//#include <SeeedOLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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
  display.print((char)247); 
//  display.print("start:"); 
//  display.println(startnum); 
//  display.print("end:"); 
//  display.println(startnum+20); 
  
  display.display();
  delay(5000);  //waits 5 seconds, change to longer if you need more time to view the display
  startnum = startnum + 20;  //increments the starting number for the next loop by 20
  
}
