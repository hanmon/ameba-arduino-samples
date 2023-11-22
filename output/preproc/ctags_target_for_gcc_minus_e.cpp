# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubBasic_v6\\AmebaPubSubBasic_v6.ino"
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
# 22 "d:\\project\\ameba-arduino-samples\\AmebaPubSubBasic_v6\\AmebaPubSubBasic_v6.ino"
# 23 "d:\\project\\ameba-arduino-samples\\AmebaPubSubBasic_v6\\AmebaPubSubBasic_v6.ino" 2
# 24 "d:\\project\\ameba-arduino-samples\\AmebaPubSubBasic_v6\\AmebaPubSubBasic_v6.ino" 2
# 25 "d:\\project\\ameba-arduino-samples\\AmebaPubSubBasic_v6\\AmebaPubSubBasic_v6.ino" 2
// Update these with values suitable for your network.

// char ssid[] = "boo";     // your network SSID (name)
// char pass[] = "@a123456";  // your network password
char ssid[] = "Bruce"; // your network SSID (name)
char pass[] = "ims.1qaz"; // your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status


char mqttServer[] = "iot.cht.com.tw"; //domain of CHT IoT Platform
char deviceId[] = "31080836893"; //Device ID for your IoT device
const char DEVICE_KEY[] = "DKMS3R2SGRE42USE5Z"; //Device Key of your IoT Device
char clientId[] = "AmebaClient1"; //MQTT Client ID


char topicBaseUrl[] = "/v1/device/";

char logStr[200]; //for printing log string

char pubSensorId[] = "vSensor"; //Sensor ID for publishing data
char subSensorId[] = "vActuator"; //Sensor ID for subscribing state

int pubInterval = 5000; //Interval for Publishing MQTT Message, unit:msec
//define ledPin, for emulating the action of relay
const int ledPin = 9;


//instantiate PubSubCluent object
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  //Enter this callback functon when a MQTT message arrived
  //Parsing JSON Object and print to serial monitor

  Serial.println((reinterpret_cast<const __FlashStringHelper *>(("Message arrived:"))));
  Serial.println((char*)payload);
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
  //emulating relay, turn on led if value=1
  relayAction(value);
}
void relayAction(unsigned long value) {
  if (value == 1) {
    digitalWrite(ledPin, 0x0);
  }
  else {
    digitalWrite(ledPin, 0x1);
  }
}

void pubTask() {
  static unsigned long previousPubTime = 0; //storing previous publishing time
  char publishTopic[100];
  //Preparing topic like "/v1/device/{deviceId}/rawdata";
  rtl_sprintf(publishTopic, "%s%s/rawdata", topicBaseUrl, deviceId);

  //Publishing sensor data after given interval
  if ((millis() - previousPubTime) > pubInterval) {
    previousPubTime = millis();
    //Gernerating 100 random values. Please repalce this by the real sensor data from your code

    int sensorValues[100];
    for (int i = 0; i < 100; i++) {
      sensorValues[i] = random(0, 100);
    }
    //Generating MQTT Payload by function "generateMqttMessage()", which is using ArduinoJSON library(v6)
    char* mqttMessage = generateJsonPayload(pubSensorId, sensorValues, 100);
    //if generating failed for some reason, leave log message and return to main loop
    if (mqttMessage == __null) {
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
    result == 0x1 ? Serial.println((reinterpret_cast<const __FlashStringHelper *>(("MQTT publish succeeded")))) : Serial.println((reinterpret_cast<const __FlashStringHelper *>(("MQTT publish failed"))));
    //Be sure to free memory dynamic allocated in function "generateMqttMessage()"
    vPortFree(mqttMessage);
  }
}

void reconnect() {
  // Loop until we're reconnected
  char subscribeTopic[50];
  //Preparing topic like "/v1/device/{deviceId}/sensor/relay/rawdata";
  rtl_sprintf(subscribeTopic, "%s%s/sensor/%s/rawdata", topicBaseUrl, deviceId, subSensorId);
  Serial.println();
  Serial.println(subscribeTopic);
  while (!client.connected()) {
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(("Attempting MQTT connection..."))));
    // Attempt to connect
    if (client.connect(clientId, DEVICE_KEY, DEVICE_KEY)) {
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(("connected"))));
      // Once connected, publish an announcement...
      //client.publish(publishRawTopic, publishRawPayload);
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    } else {
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
  //Initializing UART and setting baud rate as 38400bps
  Serial.begin(38400);

  //Try to connect to given WLAN network
  while (status != WL_CONNECTED) {
    Serial.println("");
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(("Attempting to connect to SSID: "))));
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
  pinMode(ledPin, 0x01);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  pubTask();
}
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubBasic_v6\\JsonPayload.ino"
char* generateJsonPayload(char* sensorId, int* values, int valuesNum) {
  //Calculating needed capacity for preparing MQTT Payload(JSON)
  //Using tool provided by ArduinoJSON,at https://arduinojson.org/v6/assistant/
  int capacity = ((1) * sizeof(ArduinoJson690_000::VariantSlot)) + ((valuesNum) * sizeof(ArduinoJson690_000::VariantSlot)) + ((2) * sizeof(ArduinoJson690_000::VariantSlot)) + 20;
  //Allocating Memory pool for preparing MQTT Payload(JSON)
  DynamicJsonDocument doc(capacity);
  //Creating JSON Array by JsonDocument
  JsonArray arrayRoot = doc.to<JsonArray>();
  //Creating an JSON Object in the root Array
  JsonObject obj1 = arrayRoot.createNestedObject();
  obj1["id"] = sensorId;
  //Creating an inner array of the JSON Object
  JsonArray arrayInner = obj1.createNestedArray("value");
  int count = 0;
  //Add values to the innner array
  for (int i = 0; i < valuesNum; i++) {
    //Count failed times of adding values
    if (arrayInner.add(values[i]) == 0x0) {
      count++;
    }
  }
  Serial.print("JSON Array adding failed times:" );
  Serial.println(count);
  //Printing serialized JSON string to Serial for verification
  int jsonStrSize = serializeJson(doc, Serial);
  //Allocating memory space and copying serialized JSON string to the space
  char* jsonPayloadPtr = (char*)pvPortMalloc(jsonStrSize+1);
  //  Serial.print("strlen(messageBodyPtr):"+strlen(messageBodyPtr));
  serializeJson(doc, jsonPayloadPtr, jsonStrSize + 1);
  //if JSON String is too large, printing warning message and return to main loop
  //To send larger pcaket up to 1024bytes, please modify the MQTT_MAX_PACKET_SIZE in "#ifdef MQTT_PCN001_ENLARGE_PACKET_SIZE" in PubSubClient.h
  if (jsonStrSize > 512) {
    Serial.println("\r\nGenerated MQTT payload is too large for PubSubClient to send.");
    return __null;
  }
  //return the address of prepared MQTT payload
  return jsonPayloadPtr;
}