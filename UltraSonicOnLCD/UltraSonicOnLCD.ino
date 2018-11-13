/*
   Measuring distance by HC-SR04 or US-100 connected with ameba arduino and printing on I2C LCD
   Connecting trigger pin and echo pin to ameba pin12 and pin13
   By Bruce Chiu
*/
//including I2C LCD related libraries
// LCM1602 I2C LCD
#include <Wire.h>   //Include I2C Library
#include <LiquidCrystal_I2C.h>  //Include I2C LCD Library
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int trigPin = 12;
const int echoPin = 13;
float distance = 0, prevDistance = 0;
unsigned long duration = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.print(9600);
  //set trig an echo pin mode
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //initializing I2C LCD
  lcd.begin(16, 2);
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
  trigger();
  //measuring pulse width of high from echoPin
  duration = pulseIn(echoPin, HIGH);
  distance = duration /58.0; //Calculate distance from pulse duration
  Serial.println("Distance:" + String(distance) + " cm");
  if (distance != prevDistance) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(0, 1);
    lcd.print(String(distance) + " cm");
    prevDistance = distance;
  }
  delay(2000);
}

void trigger() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}


