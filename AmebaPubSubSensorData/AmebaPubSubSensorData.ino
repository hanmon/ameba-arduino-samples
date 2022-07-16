/*
  MQTT Publish/Subscribe and JSON Serialization/Deserialization example

  This sketch demonstrates how to use the PubSubClient(provided by Realtek Ameba) and ArduinoJSON(v6) library
  to upload data to CHT IoT Platform
  It connects to CHT IoT Platform and:
  - publishes 100 random integer values to the topic of sensor "vSensor" every 5 seconds
  - subscribes to the topic of sensor "vActuator", printing out any messages
    it receives.
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function.

  This program is based on sample program from Realtek Ameba example "AmebaMQTTClient-mqtt_basic"
  Created 2019/07/06
  By Bruce Chiu
  Modified 2019/07/06
  By Bruce Chiu
  Email:boo.chiu@gmail.com
*/
#define ARDUINOJSON_ENABLE_PROGMEM 0   //Defining for ameba arduino specially 
#define DEBUG    //Uncomment this when printing degugging message is necessary
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
// Update these with values suitable for your network.

char ssid[] = "iotlab";     // your network SSID (name)
char pass[] = "";  // your network password
int status  = WL_IDLE_STATUS;    // the Wifi radio's status


char mqttServer[]     = "iot.cht.com.tw";  //domain of CHT IoT Platform
char deviceId[]       = "17598687058";     //Device ID for your IoT device
const char DEVICE_KEY[] = "";   //Device Key of your IoT Device
char clientId[]       = "AmebaClient1";  //MQTT Client ID


char topicBaseUrl[] = "/v1/device/";

char logStr[200]; //for printing log string

char pubSensorId[] = "vSensor"; //Sensor ID for publishing data
char subSensorId[] = "vActuator"; //Sensor ID for subscribing state

int pubInterval = 5000;         //Interval for Publishing MQTT Message, unit:msec
//define ledPin, for emulating the action of relay
const int ledPin = 13;


//instantiate PubSubCluent object
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  //Enter this callback functon when a MQTT message arrived
  //Parsing JSON Object and print to serial monitor

  Serial.println(F("Message arrived:"));
  Serial.println((char*)payload);
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
  //emulating relay, turn on led if value=1
  relayAction(value);
}
void relayAction(unsigned long value) {
  if (value == 1) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

void pubTask() {
  static unsigned long previousPubTime = 0;     //storing previous publishing time
  char publishTopic[100];
  //Preparing topic like "/v1/device/{deviceId}/rawdata";
  sprintf(publishTopic, "%s%s/rawdata", topicBaseUrl, deviceId);

  //Publishing sensor data after given interval
  if ((millis() - previousPubTime) > pubInterval) {
    previousPubTime = millis();
    //Gernerating 100 random values. Please repalce this by the real sensor data from your code

    int sensorValues[100];
    for (int i = 0; i < 100; i++) {
      sensorValues[i] = random(0, 100);
    }
    //Generating MQTT Payload by function "generateMqttMessage()", which is using ArduinoJSON library(v6)
    char* mqttMessage = generateJsonPayload(pubSensorId,sensorValues,100);
    //char* mqttMessage = generateJsonPayloadMultiSensors();
    //if generating failed for some reason, leave log message and return to main loop
    if (mqttMessage == NULL) {
      Serial.println("Generating MQTT Payload failed.");
      return;
    }
    //logging and printing MQTT payload for debugging
    Serial.print("\r\nPayload for MQTT Publishing:");
    Serial.println(mqttMessage);
    Serial.print("Length of MQTT Payload:");
    Serial.println(strlen(mqttMessage));

    //Publishing prepared MQTT Message and check if succeeded
    //boolean result = client.publish(publishTopic, mqttMessage,strlen(mqttMessage));
    boolean result = client.publish(publishTopic, mqttMessage, strlen(mqttMessage)+1);
    result == true ? Serial.println(F("MQTT publish succeeded")) : Serial.println(F("MQTT publish failed"));
    //Be sure to free memory dynamic allocated in function "generateMqttMessage()"
    free(mqttMessage);
  }
}

void reconnect() {
  // Loop until we're reconnected
  char subscribeTopic[50];
  //Preparing topic like "/v1/device/{deviceId}/sensor/relay/rawdata";
  sprintf(subscribeTopic, "%s%s/sensor/%s/rawdata", topicBaseUrl, deviceId, subSensorId);
  Serial.println();
  Serial.println(subscribeTopic);
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
  //Initializing UART and setting baud rate as 38400bps
  Serial.begin(38400);
  //init serial port for PM2.5
  initUART2();
  //Try to connect to given WLAN network
  while (status != WL_CONNECTED) {
    Serial.println("");
    Serial.print(F("Attempting to connect to SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  //Connecting to MQTT broker of CHT IoT Platform
  client.setServer(mqttServer, 1883);
  //Setting callback function for receiving MQTT Message
  client.setCallback(callback);

  // Allow the hardware to sort itself out
  delay(1500);
  // initialize digital pin 13 as an output.
  pinMode(ledPin, OUTPUT);
  //Initiation DHT sensor
  initDHT();
}

void loop()
{
  static unsigned long previousSensingTime = 0;
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  pubTask();
  //print sensor values
//  if (millis() - previousSensingTime > 2000) {
//    previousSensingTime=millis();
//    int uvalue = getUVData();
//    float humid = getHumidityValue();
//    float temp = getTemperatureValue();
//    Serial.print("uvalue:");
//    Serial.println(uvalue);
//    Serial.print("humid:");
//    Serial.println(humid);
//    Serial.print("temp:");
//    Serial.println(temp);
//  }

}
