//Generating a complete three value MQTT Message for uploading to CHT IoT Platform
char* generateMqttRequestBody(char* sensorId, int* values,int valuesNum) {
  const int BUFFER_SIZE = JSON_OBJECT_SIZE(2) + JSON_ARRAY_SIZE(valuesNum);
  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
  
  JsonArray& arrayRoot = jsonBuffer.createArray();
 
  JsonObject& obj1 = arrayRoot.createNestedObject();
  obj1["id"]="cnc";
  JsonArray& arrayInner = obj1.createNestedArray("value");
  int count=0;
  for (int i = 0; i < valuesNum; i++) {
    if(arrayInner.add(values[i])==false){
      count++;
    }
  }
  Serial.println("Array add failed times:"+String(count));
  //array1.add(obj1);
  int arraySize = arrayRoot.prettyPrintTo(Serial);
  char* messageBodyPtr=(char*)malloc(arraySize);
//  Serial.print("strlen(messageBodyPtr):"+strlen(messageBodyPtr));
  arrayRoot.printTo(messageBodyPtr,arraySize);
//  Serial.println("");
  Serial.print("arraySize:");
  Serial.println(arraySize);
  return messageBodyPtr;
  
  


}





char* generateMQTTMessage(float humid, float temp) {
  char *ptr1, *ptr2, *message;
  ptr1 = generateJSONObject("humidity", humid);
  ptr2 = generateJSONObject("temperature", temp);
  // ptr3=generateJSONObject("pm25",pm25);
  message = (char*)malloc(strlen(ptr1) + strlen(ptr2) + 10);
  Serial.print("Memory allocated for MQTTMessage:");
  Serial.println(strlen(ptr1) + strlen(ptr2) + 10);
  strcpy(message, "[");
  strcat(message, ptr1);
  strcat(message, ",");
  strcat(message, ptr2);
  //  strcat(message, ",");
  //  strcat(message, ptr3);
  strcat(message, "]");
#ifdef DEBUG
  Serial.print("message");   //for debugging
  Serial.println(message);   //for debugging
  Serial.print("message length:");//for debugging
  Serial.println(strlen(message));//for debugging
#endif
  free(ptr1);
  free(ptr2);
  //free(ptr3);
  return message;
}
char* generateMQTTMessage(float humid, float temp, int pm25) {
  char *ptr1, *ptr2, *ptr3, *message;
  ptr1 = generateJSONObject("humidity", humid);
  ptr2 = generateJSONObject("temperature", temp);
  ptr3 = generateJSONObject("pm25", pm25);
  message = (char*)malloc(strlen(ptr1) + strlen(ptr2) + strlen(ptr3) + 10);
  Serial.print("Memory allocated for MQTTMessage:");
  Serial.println(strlen(ptr1) + strlen(ptr2) + strlen(ptr3) + 10);

  strcpy(message, "[");
  strcat(message, ptr1);
  strcat(message, ",");
  strcat(message, ptr2);
  strcat(message, ",");
  strcat(message, ptr3);
  strcat(message, "]");
#ifdef DEBUG
  Serial.print("message");   //for debugging
  Serial.println(message);   //for debugging
  Serial.print("message length:");//for debugging
  Serial.println(strlen(message));//for debugging
#endif
  free(ptr1);
  free(ptr2);
  free(ptr3);
  return message;
}

//Generating a complete five value MQTT Message for uploading to CHT IoT Platform
char* generateMQTTMessage(float humid, float temp, int pm1, int pm25, int pm10) {
  char *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *message;
  ptr1 = generateJSONObject("humidity", humid);
  ptr2 = generateJSONObject("temperature", temp);
  ptr3 = generateJSONObject("pm1", pm1);
  ptr4 = generateJSONObject("pm25", pm25);
  ptr5 = generateJSONObject("pm10", pm10);
  message = (char*)malloc(strlen(ptr1) + strlen(ptr2) + strlen(ptr3) + strlen(ptr4) + strlen(ptr5) + 10);
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
#ifdef DEBUG
  Serial.print("message");   //for debugging
  Serial.println(message);   //for debugging
  Serial.print("message length:");//for debugging
  Serial.println(strlen(message));//for debugging
#endif
  free(ptr1);
  free(ptr2);
  free(ptr3);
  free(ptr4);
  free(ptr5);
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
  ptr = (char*)malloc(root.measureLength() + 1);
  root.printTo(ptr, root.measureLength() + 1);
  return ptr;
}
