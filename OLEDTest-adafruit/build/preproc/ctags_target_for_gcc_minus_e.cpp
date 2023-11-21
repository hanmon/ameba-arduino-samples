# 1 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino"
//#include <Wire.h>
//#include <SeeedOLED.h>
# 4 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino" 2
# 5 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino" 2
# 6 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino" 2
# 7 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino" 2
# 8 "d:\\project\\ameba-arduino-samples\\OLEDTest-adafruit\\OLEDTest-adafruit.ino" 2

Adafruit_SSD1306 display(-1);

void initOLED(){
  display.begin(0x2, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0,0);
  display.println("I'm Ameba!");
  display.setTextColor(0, 1); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(1);
  display.setTextColor(1);
  display.print("0x"); display.println(0xDEADBEEF, 16);
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
  display.setTextColor(1);
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
  delay(5000); //waits 5 seconds, change to longer if you need more time to view the display
  startnum = startnum + 20; //increments the starting number for the next loop by 20

}
