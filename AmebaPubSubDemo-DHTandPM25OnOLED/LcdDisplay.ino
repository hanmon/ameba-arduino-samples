//Usgin LCD
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity

void initLCD(){
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  lcd.setCursor(0, 1);
  lcd.print("I'm Ameba");
}

void printOnLCD(String content){
  //lcd.setCursor(0,row);
  lcd.println(content);
}

void clearLCD(){
  lcd.clear();
}
