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

const int ldrPin=A0;
const int doPin=18;
int analogValue=0,prevAnalogValue=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //initializing I2C LCD
  lcd.begin(16, 2);
  //set doPin as input
  pinMode(doPin,INPUT);
  //printing welcom message
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  lcd.setCursor(0, 1);
  lcd.print("I'm Ameba");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //send trigger pulse for 10us
  analogValue=analogRead(ldrPin);
  Serial.println("Analog Value:" + String(analogValue));
//  if (analogValue != prevAnalogValue) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Analog Value:"+String(analogValue));
    lcd.setCursor(0, 1);
    String state=digitalRead(doPin)?"HIGH":"LOW";
    lcd.print("DO State:"+state);
    prevAnalogValue = analogValue;
 // }
  delay(2000);
}




