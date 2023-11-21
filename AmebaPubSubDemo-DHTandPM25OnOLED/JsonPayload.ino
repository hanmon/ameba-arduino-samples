#include <ArduinoJson.h>
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
