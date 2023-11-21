# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\AmebaPubSubDemo.ino"
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
# 17 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\AmebaPubSubDemo.ino"
# 18 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\AmebaPubSubDemo.ino" 2
# 19 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\AmebaPubSubDemo.ino" 2
# 20 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\AmebaPubSubDemo.ino" 2
// Update these with values suitable for your network.

char ssid[] = "boo"; // your network SSID (name)
char pass[] = "@a123456"; // your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status


char mqttServer[] = "iot.cht.com.tw";
char deviceId[] = "31080836893";
char clientId[] = "amebaClient";
const char DEVICE_KEY[] = "DKMS3R2SGRE42USE5Z"; //your api key
char publishRawTopic[] = "/v1/device/31080836893/rawdata";
char publishRawPayload[300] ;
char logStr[200]; //for printing log string
char subscribeTopic[] = "/v1/device/31080836893/sensor/rgb/rawdata";
unsigned long previousRawTime = 0; //storing previous publishing time
int rawTimer = 10000; //raw data timer, unit:msec
//define ledPin
const int ledPin=13;


//instantiate PubSubCluent object
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  //Parsing JSON Object and print to serial monitor

  Serial.println((reinterpret_cast<const __FlashStringHelper *>(("Message arrived:"))));
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
  rtl_sprintf(logStr,"Parsed JSON Object id:%s, time:%s, value:%d",id,time,value);
  Serial.println(logStr);
  //digitalWrite(ledPin,(*value=='1'?HIGH:LOW));  //Switch led on or off according to value
  //unsigned long color=String(value).toInt();

}

void rawTask() {
  if ((millis() - previousRawTime) > rawTimer) {
    previousRawTime = millis();
    float humid=getHumidityValue();
    float temp=getTemperatureValue();
    //char* mqttMessage=generateMQTTMessage(random(60,70),random(20,30));
    char* mqttMessage=generateMQTTMessage(humid,temp);
    //char* mqttMessage=generateMQTTMessage(random(60,70),random(20,25),random(0,1000),random(0,1000),random(0,1000));
    strcpy(publishRawPayload,mqttMessage);
    vPortFree(mqttMessage);
    //mqttMessage.toCharArray(publishRawPayload, mqttMessage.length() + 1);
    //client.publish(publishRawTopic, publishRawPayload);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(("publishRawPayload:"))));
    Serial.println(publishRawPayload);
    int result = client.publish(publishRawTopic, publishRawPayload);
    result == 1 ? Serial.println((reinterpret_cast<const __FlashStringHelper *>(("MQTT publish succeeded")))) : Serial.println((reinterpret_cast<const __FlashStringHelper *>(("MQTT publish failed"))));
  }
}

void reconnect() {
  // Loop until we're reconnected
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
  Serial.begin(38400);

  while (status != WL_CONNECTED) {
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
  //init DHT sensor
  initDHTSensor();

}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  rawTask();
}
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\DHTSensor.ino"
# 2 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\DHTSensor.ino" 2

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
# 1 "d:\\project\\ameba-arduino-samples\\AmebaPubSubDemo\\JsonPayload.ino"
//Generating a complete two value MQTT Message for uploading to CHT IoT Platform
char* generateMQTTMessage(float humid, float temp){
  char *ptr1,*ptr2,*message;
  ptr1=generateJSONObject("humidity",humid);
  ptr2=generateJSONObject("temperature",temp);
  message=(char*)pvPortMalloc(strlen(ptr1)+strlen(ptr2)+10);
  strcpy(message, "[");
  strcat(message, ptr1);
  strcat(message, ",");
  strcat(message, ptr2);
  strcat(message, "]");

  Serial.print("message"); //for debugging
  Serial.println(message); //for debugging
  Serial.print("message length:");//for debugging
  Serial.println(strlen(message));//for debugging

  vPortFree(ptr1);
  vPortFree(ptr2);
  return message;
}
//Generating a complete three value MQTT Message for uploading to CHT IoT Platform
char* generateMQTTMessage(float humid, float temp, int pm25){
  char *ptr1,*ptr2,*ptr3,*message;
  ptr1=generateJSONObject("humidity",humid);
  ptr2=generateJSONObject("temperature",temp);
  ptr3=generateJSONObject("pm25",pm25);
  message=(char*)pvPortMalloc(strlen(ptr1)+strlen(ptr2)+strlen(ptr3)+10);

  strcpy(message, "[");
  strcat(message, ptr1);
  strcat(message, ",");
  strcat(message, ptr2);
  strcat(message, ",");
  strcat(message, ptr3);
  strcat(message, "]");

  Serial.print("message"); //for debugging
  Serial.println(message); //for debugging
  Serial.print("message length:");//for debugging
  Serial.println(strlen(message));//for debugging

  vPortFree(ptr1);
  vPortFree(ptr2);
  vPortFree(ptr3);
  return message;
}

//Generating a complete five value MQTT Message for uploading to CHT IoT Platform
char* generateMQTTMessage(float humid, float temp, int pm1, int pm25, int pm10){
  char *ptr1,*ptr2,*ptr3,*ptr4,*ptr5,*message;
  ptr1=generateJSONObject("humidity",humid);
  ptr2=generateJSONObject("temperature",temp);
  ptr3=generateJSONObject("pm1",pm1);
  ptr4=generateJSONObject("pm25",pm25);
  ptr5=generateJSONObject("pm10",pm10);
  message=(char*)pvPortMalloc(strlen(ptr1)+strlen(ptr2)+strlen(ptr3)+strlen(ptr4)+strlen(ptr5)+10);
  strcpy(message, "[");
  strcat(message, ptr1);
  strcat(message, ",");
  strcat(message, ptr2);
  strcat(message, ",");
  strcat(message, ptr3);
  strcat(message, ",");
  strcat(message, ptr4);
  strcat(message, ",");
  strcat(message, ptr5);
  strcat(message, "]");

  Serial.print("message"); //for debugging
  Serial.println(message); //for debugging
  Serial.print("message length:");//for debugging
  Serial.println(strlen(message));//for debugging

  vPortFree(ptr1);
  vPortFree(ptr2);
  vPortFree(ptr3);
  vPortFree(ptr4);
  vPortFree(ptr5);
  return message;
}


//Generating single JSON object and returning the memory address
char* generateJSONObject(char* id, float sensorValue) {
  StaticJsonBuffer<200> doc;
  JsonObject& root = doc.createObject();
  root["id"] = id;
  JsonArray& value = root.createNestedArray("value");
  value.add(sensorValue);
  char *ptr;
  ptr = (char*)pvPortMalloc(root.measureLength()+1);
  root.printTo(ptr, root.measureLength() + 1);
  return ptr;
}
