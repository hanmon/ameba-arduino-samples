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
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
// Update these with values suitable for your network.

char ssid[] = "wukong2.4";     // your network SSID (name)
char pass[] = "WuKong!!";  // your network password
int status  = WL_IDLE_STATUS;    // the Wifi radio's status

char mqttServer[]     = "iot.cht.com.tw";
char deviceId[]       = "10802236687";
char clientId[]       = "amebaClient";
const char DEVICE_KEY[] = "DK2RZT3CWXFXX0AUX1";   //your api key
char publishRawTopic[]   = "/v1/device/10802236687/rawdata";
char publishRawPayload[] = "[{\"id\":\"temperature\",\"value\":[\"25\"]},"
                        "{\"id\":\"humidity\",\"value\":[\"60\"]}]";

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
  Serial.println("Message arrived ["+String(topic)+"]");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root=jsonBuffer.parseObject((char*)payload);
  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  const char* id=root["id"];
  const char* time=root["time"];
  //const char* value=root["value"][0];
  unsigned long rgbColor=root["value"][0];
  Serial.println("Parsed JSON Object id:"+String(id)+",time:"+String(time)+",value:"+String(rgbColor));
  //digitalWrite(ledPin,(*value=='1'?HIGH:LOW));  //Switch led on or off according to value
  //unsigned long rgbColor=String(value).toInt();
  
  setColor(rgbColor);
  Serial.print("RGB Color Value:");
  Serial.println(rgbColor,HEX);
}

void rawTask() {
  if ((millis() - previousRawTime) > rawTimer) {
    previousRawTime = millis();
    String mqttMessage=getJsonPayload(String(random(60,70)),String(random(20,25)));
    mqttMessage.toCharArray(publishRawPayload, mqttMessage.length() + 1);
    //client.publish(publishRawTopic, publishRawPayload);
    int result = client.publish(publishRawTopic, publishRawPayload);
    result == 1 ? Serial.println("MQTT publish succeeded") : Serial.println("MQTT publish failed");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientId, DEVICE_KEY, DEVICE_KEY)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(publishRawTopic, publishRawPayload);
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
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
    Serial.print("Attempting to connect to SSID: ");
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
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  rawTask();
}