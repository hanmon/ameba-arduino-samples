# 1 "d:\\project\\ameba-arduino-samples\\HallSensorTest\\HallSensorTest.ino"
int ledR = 9;//LED pin
int sensor = 4; //sensor pin
int val; //numeric variable

void setup()
{
 pinMode(ledR, 0x01); //set LED pin as output
 pinMode(sensor, 0x00); //set sensor pin as input
}

void loop()
{
 val = digitalRead(sensor); //Read the sensor
 if(val == 0x0) //when magnetic field is detected, turn led on
 {
  digitalWrite(ledR, 0x0);
 }
 else
 {
  digitalWrite(ledR, 0x1);
 }
}
