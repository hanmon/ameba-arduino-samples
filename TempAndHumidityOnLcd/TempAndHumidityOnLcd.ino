/*
 This example demonstrate how to integrate DHT sensor and I2C LCD Monitor
 */

#include <Wire.h>   //Include I2C Library
#include <LiquidCrystal_I2C.h>  //Include I2C LCD Library
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
// LCM1602 I2C LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
DHT dht(DHTPIN, DHTTYPE);


void setup()
{
  Serial.begin(9600);

  lcd.begin(16,2);               // initialize the lcd 
  lcd.backlight();

  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("DHT on LCD");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("I'm Ameba");
  dht.begin(); //enable dht sensor
  delay ( 2000 );
  lcd.clear();  //clear characters shown on LCD Monitor
}

void loop()
{
  
  float t=dht.readTemperature();  //read temperature and store in a variable
  float h=dht.readHumidity();     //read humidity and store in a variable
  //lcd.clear();
  Serial.println("Current temperature:"+String(t));  // for debugging
  Serial.println("Current humidity:"+String(h));  // for debugging
  if(isnan(t)||isnan(h)){   //check if DHT sensor is normal
     lcd.setCursor( 0, 0 );
     lcd.print("Failed to read");
     lcd.setCursor( 0, 1 );
     lcd.print("from DHT sensor!");
  }
  else{
    lcd.setCursor( 0, 0 );  // set cursor to first row   
    lcd.print("Temp:"+String(dht.readTemperature())+(char)0xDF+"C"); //print temperature value on LCD   
    lcd.setCursor( 0, 1 ); // set cursor to 2nd row   
    lcd.print("Humidity:"+String(dht.readHumidity())+"%");  //print humdity value on LCD   
  }
  delay(2000);
}
