//#include <Adafruit_Sensor.h>
//#include <DHT.h>
//#include <DHT_U.h>

//#define DHTTYPE DHT11
//
//DHT_Unified dht(DHTPIN, DHTTYPE);
#define DHTPIN 2

void setup() {
  Serial.begin(115200);
  pinMode(DHTPIN,INPUT);
  //digitalWrite(DHTPIN,HIGH);
  //initiating I2C LCD Module
//  initLcd();
}

void loop() {
  // Get temperature event and print its value.
  if(!getDHTSensorValues(DHTPIN)){
    Serial.println("DHT sensor read failed");
  }
  else{
    Serial.println("DHT sensor read succeeded");
    Serial.println("Temperature:"+String(readTemperature()));
    Serial.println("Humidity:"+String(readHumidity()));
  }
  delay(5000);
//  sensors_event_t event;
//  dht.temperature().getEvent(&event);
// // float valueTemperature=event.temperature;
// // String strTemperature="Temp:"+String(valueTemperature,1)+char(0xDF)+"C";
//  
//  dht.humidity().getEvent(&event);
//  float valueHumidity=event.relative_humidity;
//  String strHumidity="Humidity:"+String(valueHumidity,1)+"%";
//  Serial.println(strTemperature);
//  Serial.println(strHumidity);
//  setLcdString(strTemperature,0);
//  setLcdString(strHumidity,1);
//  delay(3000);

}
