#include "DHT.h"
#define DHTPIN 5
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);// Initialize DHT sensor.


void initDHTSensor(){
  dht.begin(); //begin analyzing DHT signal
  Serial.print("DHT Sensor Type:");
  Serial.println(DHTTYPE);
}

float getHumidityValue(){
  //return random(40,70);
  return dht.readHumidity(); 
}

float getTemperatureValue(){
  //return random(20,30);
  return dht.readTemperature(); 
}
