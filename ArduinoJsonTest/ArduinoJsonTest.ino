#define ARDUINOJSON_ENABLE_PROGMEM 0   //Defining for ameba arduino specially 
#include <ArduinoJson.h>
unsigned long latestTime=0;
const int interval=5000;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if((millis()-latestTime)>interval){
      showJsonData();
      latestTime=millis();
  }
}


void showJsonData(){
  StaticJsonDocument<200> doc;
  //char msg[200];
  doc["id"]="cnc";

  int s_size=serializeJson(doc,Serial);
  Serial.println("");
  Serial.println("s_size:"+String(s_size));
  char* strbuffer=(char*)malloc(s_size*sizeof(char));
  //Serial.println("strlen(strbuffer):"+String(strlen(strbuffer)));
  int j_size=serializeJson(doc,strbuffer,s_size+1);
  Serial.println("j_size:"+String(j_size));
  Serial.println(strbuffer);
  free(strbuffer);
}
