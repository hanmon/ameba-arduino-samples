//TempAndHumidity, Sensing by Pin6
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);// Initialize DHT sensor.
void setup()
{
  Serial.begin(115200);
  dht.begin();
  Serial.println("Temp and Humidity Test");

}
void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    //return;
  }
  else {
    Serial.print('H');
    Serial.print(',');
    Serial.print(h,1); //顯示濕度至小數點以下1位；
    Serial.print(',');
    Serial.print(t,1); //顯示溫度至小數點以下1位；
    Serial.println(',');

  }
  delay(3000);
}
