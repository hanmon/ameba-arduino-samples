#include "DHT.h"
#define DHTPIN 5 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
void initDHT(){
  dht.begin();
}
int getUVData(){
   int uvData=analogRead(A0);
   return uvData;
}

float getHumidityValue(){
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read Humidity!");
    return 0;
  }
  else{
    return h;
  }
}

float getTemperatureValue(){
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read Temperature!");
    return 0;
  }
  else{
    return t;
  }
}
