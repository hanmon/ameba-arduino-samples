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
#define ARDUINOJSON_ENABLE_PROGMEM 0   //Defining for ameba arduino specially 
#define DEBUG    //Uncomment this when printing degugging message is necessary
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
// Update these with values suitable for your network.

char ssid[] = "chtti";     // your network SSID (name)
char pass[] = "12345678";  // your network password
int status  = WL_IDLE_STATUS;    // the Wifi radio's status


char mqttServer[]     = "iot.cht.com.tw";
char deviceId[]       = "10802236687";
char clientId[]       = "amebaClient";
const char DEVICE_KEY[] = "DK2RZT3CWXFXX0AUX1";   //your api key
char publishRawTopic[]   = "/v1/device/10802236687/rawdata";
char publishRawPayload[300] ;
char logStr[200]; //for printing log string
char subscribeTopic[] = "/v1/device/10802236687/sensor/rgb/rawdata";
unsigned long previousRawTime = 0;     //storing previous publishing time
int rawTimer = 10000;         //raw data timer, unit:msec
//define ledPin
const int ledPin=13;


//instantiate PubSubCluent object
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  //Parsing JSON Object and print to serial monitor

  Serial.println(F("Message arrived:"));
  Serial.println((char*)payload);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root=jsonBuffer.parseObject((char*)payload);
  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  const char* id=root["id"];
  const char* time=root["time"];
  unsigned long value=root["value"][0];
  //Serial.println("Parsed JSON Object id:"+String(id)+",time:"+String(time)+",value:"+String(value));
  sprintf(logStr,"Parsed JSON Object id:%s, time:%s, value:%d",id,time,value);
  Serial.println(logStr);
  //digitalWrite(ledPin,(*value=='1'?HIGH:LOW));  //Switch led on or off according to value
  //unsigned long color=String(value).toInt();
  
}

void rawTask() {
  if ((millis() - previousRawTime) > rawTimer) {
    previousRawTime = millis();
    float humid=getHumidityValue();
    float temp=getTemperatureValue();
    int pm25=getPM25();
    char* mqttMessage=generateMQTTMessage(humid,temp,pm25);
    //char* mqttMessage=generateMQTTMessage(humid,temp);
    //char* mqttMessage=generateMQTTMessage(random(60,70),random(20,25),random(0,1000),random(0,1000),random(0,1000));
    strcpy(publishRawPayload,mqttMessage);
    free(mqttMessage);
    //Show humid and temp on LCD
    clearLCD();
    char* lcdStrRow0=(char*)malloc(20);
    char* lcdStrRow1=(char*)malloc(20);
    //sprintf(lcdStrRow0,"Humid:%2.2f%%",humid);
    sprintf(lcdStrRow1,"PM2.5:%d ug/m3",pm25);
    sprintf(lcdStrRow0,"Temp:%2.2f%cC",temp,0xDF);
    printOnLCD(lcdStrRow0,0);
    printOnLCD(lcdStrRow1,1);
    free(lcdStrRow0);
    free(lcdStrRow1);
    Serial.print(F("publishRawPayload:"));
    Serial.println(publishRawPayload);
    int result = client.publish(publishRawTopic, publishRawPayload);
    result == 1 ? Serial.println(F("MQTT publish succeeded")) : Serial.println(F("MQTT publish failed"));
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    // Attempt to connect
    if (client.connect(clientId, DEVICE_KEY, DEVICE_KEY)) {
      Serial.println(F("connected"));
      // Once connected, publish an announcement...
      //client.publish(publishRawTopic, publishRawPayload);
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    } else {
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
  Serial.begin(38400);

  while (status != WL_CONNECTED) {
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
  //init DHT sensor
  initDHTSensor();
  //init LCD display
  initLCD();
  //init PM2.5 Sensor
  initUART2();
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  rawTask();
}
