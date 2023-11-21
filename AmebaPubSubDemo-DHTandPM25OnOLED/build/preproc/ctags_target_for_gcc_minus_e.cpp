# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino"
/*

  Basic MQTT example



  This sketch demonstrates the basic capabilities of the library.

  It connects to an MQTT server then:

  - publishes "hello world" to the topic "outTopic"

  - subscribes to the topic "inTopic", printing out any messages

    it receives. NB - it assumes the received payloads are strings not binary



  It will reconnect to the server if the connection is lost using a blocking

  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to

  achieve the same result without blocking the main loop.



*/
# 17 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino"
# 18 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino" 2
# 19 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino" 2
# 20 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino" 2
# 21 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino" 2
# 22 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino" 2
// include headers for BMP180
# 24 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino" 2
# 25 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\AmebaPubSubDemo-DHTandPM25OnOLED.ino" 2
SetRgbLed rgb(1, 9, 10, 11);
// Update these with values suitable for your network.
// create an BMP180 object using the I2C interface

BMP180I2C bmp180(0x77);

char ssid[] = "AIoT_1"; // your network SSID (name)
char pass[] = "chtti@chtti"; // your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status

char mqttServer[] = "iot.cht.com.tw";
char deviceId[] = "31080836893";
char clientId[] = "amebaClient";
const char DEVICE_KEY[] = "DKMS3R2SGRE42USE5Z"; // your api key
char publishRawTopic[] = "/v1/device/31080836893/rawdata";
char publishRawPayload[400];
char displayRow0[30], displayRow1[30], displayRow2[30];
char logStr[200]; // for printing log string
char subscribeTopic[] = "/v1/device/31080836893/sensor/rgb/rawdata";
unsigned long previousRawTime = 0; // storing previous publishing time
int rawTimer = 500; // raw data timer, unit:msec
// define ledPin
const int ledPin = 13;

// instantiate PubSubCluent object
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  // Parsing JSON Object and print to serial monitor

  Serial.println((reinterpret_cast<const __FlashStringHelper *>(("Message arrived:"))));
  Serial.println((char *)payload);
  StaticJsonDocument<256> doc;
  auto error = deserializeJson(doc, (char*)payload);
  // Test if parsing succeeds.
  if (error) {
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(("deserializeJson() failed: "))));
    Serial.println(error.c_str());
    return;
  }
  //Parsing(Deserializing) values in JSON object
  const char* id = doc["id"];
  const char* time = doc["time"];
  unsigned long value = doc["value"][0];
  //Printing the values in MQTT Message
  rtl_sprintf(logStr, "Parsed JSON Object id:%s, time:%s, value:%d", id, time, value);
  Serial.println(logStr);
  rgb.setColor((int)value);
  // digitalWrite(ledPin,(*value=='1'?HIGH:LOW));  //Switch led on or off according to value
  // unsigned long color=String(value).toInt();
}

void rawTask()
{
  if ((millis() - previousRawTime) > rawTimer)
  {
    previousRawTime = millis();
    // Measuring from real sensors
    float humid = random(60, 70);
    float temp = random(20, 25);
    int pm10 = random(0, 1000);
    int pm25 = random(0, 1000);
    int pm100 = random(0, 1000);
    // humid=getHumidityValue();
    // temp=getTemperatureValue();
    // int* pmValues=getPMValues();
    // pm10=pmValues[0];
    // pm25=pmValues[1];
    // pm100=pmValues[2];
    // get LDR Value
    int ldrValue = analogRead(1);
    if (temp > 30)
    {
      rgb.setColor(RED);
    }
    else if (temp <= 30)
    {
      rgb.setColor(GREEN);
    }
    // get BMP180 Value
    //  start a temperature measurement
    // if (!bmp180.measureTemperature())
    // {
    //   Serial.println("could not start temperature measurement, is a measurement already running?");
    //   return;
    // }

    // wait for the measurement to finish. proceed as soon as hasValue() returned true.
    // do
    // {
    //   delay(100);
    // } while (!bmp180.hasValue());

    // Serial.print("Temperature: ");
    // float temperature = bmp180.getTemperature();
    // Serial.print(temperature, 1);
    // Serial.println(" degC");

    // start a pressure measurement. pressure measurements depend on temperature measurement, you should only start a pressure
    // measurement immediately after a temperature measurement.
    // if (!bmp180.measurePressure())
    // {
    //   Serial.println("could not start perssure measurement, is a measurement already running?");
    //   return;
    // }

    // wait for the measurement to finish. proceed as soon as hasValue() returned true.
    // do
    // {
    //   delay(100);
    // } while (!bmp180.hasValue());

    // Serial.print("Pressure: ");
    // float pressure = bmp180.getPressure();
    // Serial.print(pressure);
    // Serial.println(" Pa");

    // Generating random values for testing
    // char* mqttMessage=generateMQTTMessage(humid,temp,pm25);
    // char* mqttMessage=generateMQTTMessage(humid,temp);
    // generating testing value for publishing
    char* mqttMessage=generateMQTTMessage(humid,temp,pm10,pm25,pm100);
    // char *mqttMessage = generateMQTTMessage(temperature, pressure, ldrValue);
    // char* mqttMessage=generateMQTTMessage(humid,temp);
    // strcpy(publishRawPayload, mqttMessage);

    // free(mqttMessage);
    // Show humid and temp on LCD
    // clearLCD();
    //    char* lcdStrRow0=(char*)malloc(20);
    //    char* lcdStrRow1=(char*)malloc(20);
    // clearOLED();
    // sprintf(displayRow0, "Temp:%2.2f%cC", temp, 0xF7);
    // printOnOLED(displayRow0);
    // memset(displayRow0, 0, 30);
    // sprintf(displayRow0, "Humid:%2.2f%%", humid);
    // printOnOLED(displayRow0);
    // memset(displayRow0, 0, 30);
    // printOnOLED(displayRow0);
    // printOnOLED(displayRow1);
    // printOnOLED(displayRow2);
    // Serial.print(F("publishRawPayload:"));
    // Serial.println(mqttMessage);
    int result = client.publish(publishRawTopic, mqttMessage);
    result == 1 ? Serial.println((reinterpret_cast<const __FlashStringHelper *>(("MQTT publish succeeded")))) : Serial.println((reinterpret_cast<const __FlashStringHelper *>(("MQTT publish failed"))));
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(("Attempting MQTT connection..."))));
    // Attempt to connect
    if (client.connect(clientId, DEVICE_KEY, DEVICE_KEY))
    {
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(("connected"))));
      // Once connected, publish an announcement...
      // client.publish(publishRawTopic, publishRawPayload);
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    }
    else
    {
      Serial.print((reinterpret_cast<const __FlashStringHelper *>(("failed, rc="))));
      Serial.print(client.state());
      Serial.println((reinterpret_cast<const __FlashStringHelper *>((" try again in 5 seconds"))));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  // mySerial.begin(9600);
  Serial.begin(38400);
  // initLCD();
  initOLED();
  // Draw CHT logo
  drawBitmap();
  while (status != WL_CONNECTED)
  {
    Serial.println("");
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(("Attempting to connect to SSID: "))));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  client.setServer(mqttServer, 1883);
  client.setCallback(callback);

  // Allow the hardware to sort itself out
  delay(1500);
  // initialize digital pin 13 as an output.
  pinMode(ledPin, 0x01);
  // init DHT sensor
  initDHTSensor();
  // init LCD display

  // init PM2.5 Sensor
  clearOLED();
  initUART2();
  // initialize BMP180
  // Wire.begin();
  // if (!bmp180.begin())
  // {
  //   Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
  //   while (1)
  //     ;
  // }
  // reset sensor to default parameters.
  // bmp180.resetToDefaults();
  // // enable ultra high resolution mode for pressure measurements
  // bmp180.setSamplingMode(BMP180MI::MODE_UHR);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  rawTask();
}
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\DHTSensor.ino"
# 2 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\DHTSensor.ino" 2

// Uncomment whatever type you're using!

//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(5, 11 /* DHT 11*/);// Initialize DHT sensor.


void initDHTSensor(){
  dht.begin(); //begin analyzing DHT signal
  Serial.print("DHT Sensor Type:");
  Serial.println(11 /* DHT 11*/);
}

float getHumidityValue(){
  //return random(40,70);
  return dht.readHumidity();
}

float getTemperatureValue(){
  //return random(20,30);
  return dht.readTemperature();
}
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\JsonPayload.ino"

//Generating a complete two value MQTT Message for uploading to CHT IoT Platform

char jsonOutputStr[384];

// char* generateMQTTMessage(float humid, float temp){
//   char *ptr1,*ptr2,*message;
//   ptr1=generateJSONObject("humidity",humid);
//   ptr2=generateJSONObject("temperature",temp);
//   message=(char*)malloc(strlen(ptr1)+strlen(ptr2)+10);
//   strcpy(message, "[");
//   strcat(message, ptr1);
//   strcat(message, ",");
//   strcat(message, ptr2);
//   strcat(message, "]");
//   #ifdef DEBUG
//   Serial.print("message");   //for debugging
//   Serial.println(message);   //for debugging
//   Serial.print("message length:");//for debugging
//   Serial.println(strlen(message));//for debugging
//   #endif
//   free(ptr1);
//   free(ptr2);
//   return message;
// }
// //Generating a complete three value MQTT Message for uploading to CHT IoT Platform
// char* generateMQTTMessage(float temperature, float pressure, int ldr){
//   char *ptr1,*ptr2,*ptr3,*message;
//   ptr1=generateJSONObject("temperature",temperature);
//   ptr2=generateJSONObject("pressure",pressure);
//   ptr3=generateJSONObject("LDR",ldr);
//   message=(char*)malloc(strlen(ptr1)+strlen(ptr2)+strlen(ptr3)+20);

//   strcpy(message, "[");
//   strcat(message, ptr1);
//   strcat(message, ",");
//   strcat(message, ptr2);
//   strcat(message, ",");
//   strcat(message, ptr3); 
//   strcat(message, "]");
//   #ifdef DEBUG
//   Serial.print("message");   //for debugging
//   Serial.println(message);   //for debugging
//   Serial.print("message length:");//for debugging
//   Serial.println(strlen(message));//for debugging
//   #endif
//   free(ptr1);
//   free(ptr2);
//   free(ptr3);
//   return message;
// }

// //Generating a complete five value MQTT Message for uploading to CHT IoT Platform
// char* generateMQTTMessage(float humid, float temp, int pm1, int pm25, int pm10){
//   char *ptr1,*ptr2,*ptr3,*ptr4,*ptr5,*message;
//   ptr1=generateJSONObject("humidity",humid);
//   ptr2=generateJSONObject("temperature",temp);
//   ptr3=generateJSONObject("pm1",pm1);
//   ptr4=generateJSONObject("pm25",pm25);
//   ptr5=generateJSONObject("pm10",pm10);
//   // message=(char*)malloc(strlen(ptr1)+strlen(ptr2)+strlen(ptr3)+strlen(ptr4)+strlen(ptr5)+10);
//   strcpy(message, "[");
//   strcat(message, ptr1);
//   strcat(message, ",");
//   strcat(message, ptr2);
//   strcat(message, ",");
//   strcat(message, ptr3); 
//   strcat(message, ",");
//   strcat(message, ptr4); 
//   strcat(message, ",");
//   strcat(message, ptr5); 
//   strcat(message, "]");
//   #ifdef DEBUG
//   Serial.print("message");   //for debugging
//   Serial.println(message);   //for debugging
//   Serial.print("message length:");//for debugging
//   Serial.println(strlen(message));//for debugging
//   #endif
//   // free(ptr1);
//   // free(ptr2);
//   // free(ptr3);
//   // free(ptr4);
//   // free(ptr5);
//   return message;
// }

//Generating a complete five value MQTT Message for uploading to CHT IoT Platform
char* generateMQTTMessage(float humid, float temp, int pm1, int pm25, int pm10){
  // char *ptr1,*ptr2,*ptr3,*ptr4,*ptr5;
    StaticJsonDocument<384> doc;
    JsonObject obj1=doc.createNestedObject();
    obj1["id"]="humid";
    JsonArray data1=obj1.createNestedArray("value");
    data1.add(humid);

    JsonObject obj2=doc.createNestedObject();
    obj2["id"]="temp";
    JsonArray data2=obj2.createNestedArray("value");
    data2.add(temp);

    JsonObject obj3=doc.createNestedObject();
    obj3["id"]="pm1";
    JsonArray data3=obj3.createNestedArray("value");
    data3.add(pm1);

    JsonObject obj4=doc.createNestedObject();
    obj4["id"]="pm25";
    JsonArray data4=obj4.createNestedArray("value");
    data4.add(pm25);

    JsonObject obj5=doc.createNestedObject();
    obj5["id"]="pm10";
    JsonArray data5=obj5.createNestedArray("value");
    data5.add(pm10);

    // memset(jsonOutputStr, 0, sizeof(jsonOutputStr));
    //serializeJsonPretty(doc, Serial);
    serializeJson(doc, jsonOutputStr);
    Serial.print("jsonOutputStr：");
    Serial.println(jsonOutputStr);
    Serial.print("MQTT Message Length:");
    Serial.println(strlen(jsonOutputStr));
    return jsonOutputStr;
}

//Generating single JSON object and returning the memory address
// char* generateJSONObject(char* id, float sensorValue) {
//   StaticJsonDocument<256> doc;
//   doc["id"]=id;
//   JsonArray data=doc.createNestedArray("data");
//   data.add(sensorValue);
//   static char innerMsg[50];
//   memset(innerMsg, 0, sizeof(innerMsg));
//   serializeJson(doc,innerMsg);
//   return innerMsg;
// }

// //Generating single JSON object and returning the memory address
// char* generateJSONObject(char* id, float sensorValue) {
//   StaticJsonBuffer<200> doc;
//   JsonObject& root = doc.createObject();
//   root["id"] = id;
//   JsonArray& value = root.createNestedArray("value");
//   value.add(sensorValue);
//   char *ptr;
//   ptr = (char*)malloc(root.measureLength()+1);
//   root.printTo(ptr, root.measureLength() + 1);
//   return ptr;
// }
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\LcdDisplay.ino"
//Usgin LCD
# 3 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\LcdDisplay.ino" 2
# 4 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\LcdDisplay.ino" 2
# 5 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\LcdDisplay.ino" 2
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
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\OLEDisplay.ino"
//#include <Wire.h>
//#include <SeeedOLED.h>
# 4 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\OLEDisplay.ino" 2
# 5 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\OLEDisplay.ino" 2
# 6 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\OLEDisplay.ino" 2


Adafruit_SSD1306 display(4);


void initOLED(){
  lcd.begin(16, 2);
  display.begin(0x2, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0,0);
  display.println("I'm Ameba!");
  display.setTextColor(0, 1); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(1);
  display.setTextColor(1);
  display.print("0x"); display.println(0xDEADBEEF, 16);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void drawBitmap(){
  display.drawBitmap(0,0,CHT_logo,128,64,1);
  display.display();
}


void setTextColor(){
  display.setTextColor(1,0);
}
//void initOLED(){
//    Wire.begin();
//    SeeedOled.init();
//    SeeedOled.clearDisplay();
//    SeeedOled.setTextXY(0,0);
//    SeeedOled.putString("I'm Ameba!");
//    SeeedOled.setTextXY(1,0);
//    SeeedOled.putString("Temperature:");
//    SeeedOled.setTextXY(2,0);
//    SeeedOled.putString("Humidity:");
//    SeeedOled.setTextXY(3,0);
//    SeeedOled.putString("PM2.5:");
//}
//
void clearOLED(){
  display.clearDisplay();
}

void serCursorToBegin(){
 display.setCursor(0,0);
}

void printOnOLED(char* content){
   //display.setCursor(row,0);
   display.println(content);
   display.display();
  //  display.display();
 // delay(2000);

}
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\PM25.ino"
/*

  This example demonstrate how to read pm2.5 value on PMS 3003 air condition sensor



  PMS 3003 pin map is as follow:

    PIN1  :VCC, connect to 5V

    PIN2  :GND

    PIN3  :SET, 0:Standby mode, 1:operating mode

    PIN4  :RXD :Serial RX

    PIN5  :TXD :Serial TX

    PIN6  :RESET

    PIN7  :NC

    PIN8  :NC



  In this example, we only use Serial to get PM 2.5 value.



  The circuit: (BOARD RTL8195A)

   RX is digital pin 0 (connect to TX of PMS 3003)

   TX is digital pin 1 (connect to RX of PMS 3003)



*/
# 22 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\PM25.ino"
# 23 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo-DHTandPM25OnOLED\\PM25.ino" 2

SoftwareSerial mySerial(0, 1); // RX, TX







uint8_t buf[32];
int idx = 0;


void initUART2() {
  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600
}

int* getPMValues() { // run over and over
  uint8_t c = 0;
  idx = 0;
  int pmValues[3];
  memset(buf, 0, 32); //clear buf

  while (0x1) {
    while (c != 0x42) {
      while (!mySerial.available());
      c = mySerial.read();
    }
    while (!mySerial.available());
    c = mySerial.read();
    if (c == 0x4d) {
      // now we got a correct header)
      buf[idx++] = 0x42;
      buf[idx++] = 0x4d;
      break;
    }
  }

  while (idx != 32) {
    while (!mySerial.available());
    buf[idx++] = mySerial.read();
  }

  pmValues[0] = ( buf[10] << 8 ) | buf[11]; //Value of PM1
  pmValues[1] = ( buf[12] << 8 ) | buf[13]; //Value of PM2.5
  pmValues[2] = ( buf[14] << 8 ) | buf[15]; //Value of PM10

  Serial.print("pm1: ");
  Serial.print(pmValues[0]);
  Serial.println(" ug/m3");
  Serial.print("pm2.5: ");
  Serial.print(pmValues[1]);
  Serial.println(" ug/m3");
  Serial.print("pm10: ");
  Serial.print(pmValues[2]);
  Serial.println(" ug/m3");
  return pmValues;
}

int getPM25() { // run over and over
  uint8_t c = 0;
  idx = 0;
  int pm10 = 0;
  int pm25 = 0;
  int pm100 = 0;
  memset(buf, 0, 32); //clear buf

  while (0x1) {
    while (c != 0x42) {
      while (!mySerial.available());
      c = mySerial.read();
    }
    while (!mySerial.available());
    c = mySerial.read();
    if (c == 0x4d) {
      // now we got a correct header)
      buf[idx++] = 0x42;
      buf[idx++] = 0x4d;
      break;
    }
  }

  while (idx != 32) {
    while (!mySerial.available());
    buf[idx++] = mySerial.read();
  }

  pm10 = ( buf[10] << 8 ) | buf[11];
  pm25 = ( buf[12] << 8 ) | buf[13];
  pm100 = ( buf[14] << 8 ) | buf[15];

  Serial.print("pm2.5: ");
  Serial.print(pm25);
  Serial.println(" ug/m3");
  return pm25;
}
