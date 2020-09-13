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
