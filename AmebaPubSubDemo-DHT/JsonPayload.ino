String getJsonPayload(String humid, String temp) {
  StaticJsonBuffer<200> doc1;
  StaticJsonBuffer<200> doc2; //allocated for JSON document
  JsonObject& root1 = doc1.createObject();
  JsonObject& root2 = doc2.createObject();
  root1["id"] = "humidity";
  JsonArray& value1 = root1.createNestedArray("value");
  value1.add(humid);
  root2["id"] = "temperature";
  JsonArray& value2 = root2.createNestedArray("value");
  value2.add(temp);
  String output1, output2;
  root1.printTo(output1);
  root2.printTo(output2);
  String message = "[" + output1 + "," + output2 + "]";
  return message;
}