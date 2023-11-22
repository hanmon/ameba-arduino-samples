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
#define ARDUINOJSON_ENABLE_PROGMEM 0 // Defining for ameba arduino specially
#define DEBUG                        // Uncomment this when printing degugging message is necessary
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "SetRgbLed.h"
#include "CHT_logo.h"
// include headers for BMP180
#include <Wire.h>
#include <BMP180I2C.h>
SetRgbLed rgb(COMMON_ANODE, 9, 10, 11);
// Update these with values suitable for your network.
// create an BMP180 object using the I2C interface
#define I2C_ADDRESS 0x77
BMP180I2C bmp180(I2C_ADDRESS);

char ssid[] = "Bruce";    // your network SSID (name)
char pass[] = "ims.1qaz"; // your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status

char mqttServer[] = "iot.cht.com.tw";
char deviceId[] = "31080836893";
char clientId[] = "amebaClient";
const char DEVICE_KEY[] = "DKMS3R2SGRE42USE5Z"; // your api key
char publishRawTopic[] = "/v1/device/31080836893/rawdata";
char publishRawPayload[400];
char displayRow0[30], displayRow1[30], displayRow2[30],displayRow3[30],displayRow4[30];
char logStr[200]; // for printing log string
char subscribeTopic[] = "/v1/device/31080836893/sensor/rgb/rawdata";
unsigned long previousRawTime = 0; // storing previous publishing time
int rawTimer = 500;               // raw data timer, unit:msec
// define ledPin
const int ledPin = 13;

// instantiate PubSubCluent object
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  // Parsing JSON Object and print to serial monitor

  Serial.println(F("Message arrived:"));
  Serial.println((char *)payload);
  StaticJsonDocument<256> doc;
  auto error = deserializeJson(doc, (char*)payload);
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  //Parsing(Deserializing) values in JSON object
  const char* id = doc["id"];
  const char* time = doc["time"];
  unsigned long value = doc["value"][0];
  //Printing the values in MQTT Message
  sprintf(logStr, "Parsed JSON Object id:%s, time:%s, value:%d", id, time, value);
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
    // generating random sensor values
    float humid = random(60, 70);
    float temp = random(20, 25);
    int pm10 = random(0, 1000);
    int pm25 = random(0, 1000);
    int pm100 = random(0, 1000);
    // Measuring from real sensors
    // humid=getHumidityValue();
    // temp=getTemperatureValue();
    // int* pmValues=getPMValues();
    // pm10=pmValues[0];
    // pm25=pmValues[1];
    // pm100=pmValues[2];
    // get LDR Value
    int ldrValue = analogRead(A0);
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
     //clearOLED();
     serCursorToBegin();
     setTextColor();
     sprintf(displayRow0, "Temp:%2.2f%cC", temp, 0xF7);
     printOnOLED(displayRow0);
    // memset(displayRow0, 0, 30);
     sprintf(displayRow1, "Humid:%2.2f%%", humid);
     printOnOLED(displayRow1);

     sprintf(displayRow2, "PM1:%d", pm10);
     printOnOLED(displayRow2);

     sprintf(displayRow3, "PM2.5:%d", pm25);
     printOnOLED(displayRow3);

     sprintf(displayRow4, "PM10:%d", pm100);
     printOnOLED(displayRow4);
    // memset(displayRow0, 0, 30);
    // printOnOLED(displayRow0);
    // printOnOLED(displayRow1);
    // printOnOLED(displayRow2);
    // Serial.print(F("publishRawPayload:"));
    // Serial.println(mqttMessage);
    int result = client.publish(publishRawTopic, mqttMessage);
    result == 1 ? Serial.println(F("MQTT publish succeeded")) : Serial.println(F("MQTT publish failed"));
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print(F("Attempting MQTT connection..."));
    // Attempt to connect
    if (client.connect(clientId, DEVICE_KEY, DEVICE_KEY))
    {
      Serial.println(F("connected"));
      // Once connected, publish an announcement...
      // client.publish(publishRawTopic, publishRawPayload);
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    }
    else
    {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again in 5 seconds"));
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
    Serial.print(F("Attempting to connect to SSID: "));
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
  pinMode(ledPin, OUTPUT);
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
