//Generating(Serializing) MQTT Payload function for uploading to CHT IoT Platform
char* generateJsonPayload(char* sensorId, int* values, int valuesNum) {
  //Calculating needed capacity for preparing MQTT Payload(JSON)
  //Using tool provided by ArduinoJSON,at https://arduinojson.org/v6/assistant/
  int capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(valuesNum) + JSON_OBJECT_SIZE(2) + 20;
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
    if (arrayInner.add(values[i]) == false) {
      count++;
    }
  }
  if (count > 0) {
    Serial.print("JSON Array adding failed times:" );
    Serial.println(count);
  }

  //Printing serialized JSON string to Serial for verification
  int jsonStrSize = serializeJson(doc, Serial);
  Serial.println();
  //Allocating memory space and copying serialized JSON string to the space
  char* jsonPayloadPtr = (char*)malloc(jsonStrSize + 2);
  //  Serial.print("strlen(messageBodyPtr):"+strlen(messageBodyPtr));
  serializeJson(doc, jsonPayloadPtr, jsonStrSize + 1);

  //return the address of prepared MQTT payload
  return jsonPayloadPtr;
}


char* generateJsonPayloadMultiSensors() {
  //Calculating needed capacity for preparing MQTT Payload(JSON)
  //Using tool provided by ArduinoJSON,at https://arduinojson.org/v6/assistant/
  int capacity = 5*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(5) + 5*JSON_OBJECT_SIZE(2);
  //Allocating Memory pool for preparing MQTT Payload(JSON)
  DynamicJsonDocument doc(capacity);
  //Creating JSON Array by JsonDocument
  JsonArray arrayRoot = doc.to<JsonArray>();
  //Creating first JSON Object in the root Array
  JsonObject obj1 = arrayRoot.createNestedObject();
  obj1["id"] = "uv_sensor";
  //Creating an inner array of the JSON Object
  JsonArray arrayInner1 = obj1.createNestedArray("value");
  int uvData=getUVData();
  arrayInner1.add(uvData);

   //Creating 2nd JSON Object in the root Array
  JsonObject obj2 = arrayRoot.createNestedObject();
  obj2["id"] = "humidity";
  //Creating an inner array of the JSON Object
  JsonArray arrayInner2 = obj2.createNestedArray("value");
  float humid=getHumidityValue();
  arrayInner2.add(humid);

   //Creating 3rd JSON Object in the root Array
  JsonObject obj3 = arrayRoot.createNestedObject();
  obj3["id"] = "temperature";
  //Creating an inner array of the JSON Object
  JsonArray arrayInner3 = obj3.createNestedArray("value");
  float temp=getTemperatureValue();
  arrayInner3.add(temp);

  JsonObject obj4 = arrayRoot.createNestedObject();
  obj4["id"] = "pm25";
  //Creating an inner array of the JSON Object
  JsonArray arrayInner4 = obj4.createNestedArray("value");
  //float pm25=getPM25();
  float pm25=random(0,1000);
  arrayInner4.add(pm25);

  JsonObject obj5 = arrayRoot.createNestedObject();
  obj5["id"] = "light";
  //Creating an inner array of the JSON Object
  JsonArray arrayInner5 = obj5.createNestedArray("value");
  //float pm25=getPM25();
  float light=getLightData();
  arrayInner5.add(light);
  
  //Printing serialized JSON string to Serial for verification
  int jsonStrSize = serializeJson(doc, Serial);
  //Allocating memory space and copying serialized JSON string to the space
  char* jsonPayloadPtr = (char*)malloc(jsonStrSize+1);
  //  Serial.print("strlen(messageBodyPtr):"+strlen(messageBodyPtr));
  serializeJson(doc, jsonPayloadPtr, jsonStrSize + 1);
  //if JSON String is too large, printing warning message and return to main loop
  //To send larger pcaket up to 1024bytes, please modify the MQTT_MAX_PACKET_SIZE in "#ifdef MQTT_PCN001_ENLARGE_PACKET_SIZE" in PubSubClient.h
  if (jsonStrSize > 1000) {
    Serial.println("\r\nGenerated MQTT payload is too large for PubSubClient to send.");
    return NULL;
  }
  //return the address of prepared MQTT payload
  return jsonPayloadPtr;
}
