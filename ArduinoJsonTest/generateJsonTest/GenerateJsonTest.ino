#define ARDUINOJSON_ENABLE_PROGMEM 0 // Defining for ameba arduino specially
#include <ArduinoJson.h>
#include <stdio.h>
StaticJsonDocument<512> doc;
void setup()
{
    Serial.begin(38400);
    float humid = random(60, 70);
    float temp = random(20, 25);
    int pm1 = random(0, 1000);
    int pm25 = random(0, 1000);
    int pm10 = random(0, 1000);
    //JsonArray array1= doc.createNestedArray();
    JsonObject obj1=doc.createNestedObject();
    obj1["id"]="humid";
    JsonArray data1=obj1.createNestedArray("data");
    data1.add(humid);

    JsonObject obj2=doc.createNestedObject();
    obj2["id"]="temp";
    JsonArray data2=obj2.createNestedArray("data");
    data2.add(temp);

    JsonObject obj3=doc.createNestedObject();
    obj3["id"]="pm1";
    JsonArray data3=obj3.createNestedArray("data");
    data3.add(pm1);

    JsonObject obj4=doc.createNestedObject();
    obj4["id"]="pm25";
    JsonArray data4=obj4.createNestedArray("data");
    data4.add(pm25);

    JsonObject obj5=doc.createNestedObject();
    obj5["id"]="pm10";
    JsonArray data5=obj5.createNestedArray("data");
    data5.add(pm10);
    

    
    // doc["id"] = "humid";
    // JsonArray data = doc.createNestedArray("data");
    // data.add(humid);

    // doc["id"] = "temp";
    // data.add(temp);

    // doc["id"] = "pm1";
    // data.add(pm1);

    // doc["id"] = "pm25";
    // data.add(pm25);

    // doc["id"] = "pm10";
    // data.add(pm10);

    serializeJsonPretty(doc, Serial);
}

void loop()
{
}