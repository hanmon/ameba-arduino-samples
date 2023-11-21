//#include <Wire.h>
//#include <SeeedOLED.h>
#include <Wire.h>
#include <BMP180I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "CHT_logo.h"
#include "LASS.h"
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
#define I2C_ADDRESS 0x77
// create an BMP180 object using the I2C interface
BMP180I2C bmp180(I2C_ADDRESS);

void initOLED()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("This is Size 2");
  display.setTextSize(2);
  display.println("This is Size 2");
  display.setTextSize(1);
  display.println("This is Size 1");
  display.setTextSize(1);
  display.println("This is Size 1");
  display.setTextSize(1);
  display.println("This is Size 1");
  display.setTextSize(1);
  display.println("This is Size 1");
  display.display();
  delay(5000);
  display.clearDisplay();
}

void clearOLED()
{
  display.clearDisplay();
}

void serCursorToBegin()
{
  display.setCursor(0, 0);
}

void printOnOLED(char *content)
{
  // display.setCursor(row,0);
  display.println(content);
  display.display();
  //  display.display();
  // delay(2000);
}
void setup()
{
  initOLED();
  // init PM2.5 Sensor
  //  initUART2();
  display.drawBitmap(0, 0, CHT_logo, 128, 64, 1);
  display.display();
  delay(5000);
  display.clearDisplay();
  display.drawBitmap(0, 0, LASS, 128, 64, 1);
  display.display();
  delay(5000);
  // initialize BMP180
  Wire.begin();
  if (!bmp180.begin())
  {
    Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
    while (1)
      ;
  }
  // reset sensor to default parameters.
  bmp180.resetToDefaults();
  // enable ultra high resolution mode for pressure measurements
  bmp180.setSamplingMode(BMP180MI::MODE_UHR);
}
int startnum = 241;
void loop()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // get BMP180 value
  //  put your main code here, to run repeatedly:

  delay(1000);

  // start a temperature measurement
  if (!bmp180.measureTemperature())
  {
    Serial.println("could not start temperature measurement, is a measurement already running?");
    return;
  }

  // wait for the measurement to finish. proceed as soon as hasValue() returned true.
  do
  {
    delay(100);
  } while (!bmp180.hasValue());

  Serial.print("Temperature: ");
  float temperature=bmp180.getTemperature();
  Serial.print(temperature,1);
  Serial.println(" degC");

  // start a pressure measurement. pressure measurements depend on temperature measurement, you should only start a pressure
  // measurement immediately after a temperature measurement.
  if (!bmp180.measurePressure())
  {
    Serial.println("could not start perssure measurement, is a measurement already running?");
    return;
  }

  // wait for the measurement to finish. proceed as soon as hasValue() returned true.
  do
  {
    delay(100);
  } while (!bmp180.hasValue());

  Serial.print("Pressure: ");
  float pressure=bmp180.getPressure();
  Serial.print(pressure);
  Serial.println(" Pa");

  display.setTextSize(1);
  display.println("Temperature:");
  display.setTextSize(2);
  display.println(temperature);
  display.setTextSize(1);
  display.println("Pressure:");
  display.setTextSize(2);
  display.println(pressure);
  display.display();
  delay(5000);              // waits 5 seconds, change to longer if you need more time to view the display
 
}
