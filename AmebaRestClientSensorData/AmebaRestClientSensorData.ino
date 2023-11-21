#define ARDUINOJSON_ENABLE_PROGMEM 0   //Defining for ameba arduino specially 
#include <WiFi.h>
#include <ArduinoJson.h>
char ssid[] = "boo"; //  your network SSID (name)
char pass[] = "@a123456";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
//IPAddress server(64,233,189,94);  // numeric IP for Google (no DNS)
char server[] = "iot.cht.com.tw";    // name address for Google (using DNS)
char baseURL[] = "/iot/v1";
unsigned long postInterval = 3000; //Interval of sending http request
char deviceId[]       = "31080836893";     //Device ID for your IoT device
const char DEVICE_KEY[] = "DKMS3R2SGRE42USE5Z";   //Device Key of your IoT Device
char postSensorId[] = "vSensor";

WiFiClient client;
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(38400);
  initUART2();
  while (!Serial) {
    ;
  }
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("\nConnected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
  }

  initDHT();
}

void loop() {
  static unsigned long previousReconnectTime = 0;
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, pass);

      // wait 10 seconds for connection:
      delay(10000);
    }
    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    if (millis() - previousReconnectTime > 3000) {
      previousReconnectTime = millis();
      if (client.connect(server, 80)) {
        Serial.println("connected to server");
      }
    }
  }
  //reconnect

  postTask();

}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void postTask() {
  static unsigned long previousPostTime = 0;     //storing previous publishing time
  char strBuffer[200];
  //Publishing sensor data after given interval
  if ((millis() - previousPostTime) > postInterval) {
    previousPostTime = millis();
    //Gernerating 100 random values. Please repalce this by the real sensor data from your code

    int sensorValues[400];
    for (int i = 0; i < 400; i++) {
      sensorValues[i] = random(0, 100);
    }

    if (client.connected() && WiFi.status() == WL_CONNECTED) {
      //Generating MQTT Payload by function "generatehttpPayload()", which is using ArduinoJSON library(v6)
      char* httpPayload = generateJsonPayloadMultiSensors();
      //if generating failed for some reason, leave log message and return to main loop
      if (httpPayload == NULL) {
        Serial.println("Generating HTTP Payload failed.");
        return;
      }
      // Make a HTTP request:
      sprintf(strBuffer, "POST /iot/v1/device/%s/rawdata HTTP/1.1", deviceId);
      client.println(strBuffer);
      client.println("Host: iot.cht.com.tw");
      sprintf(strBuffer, "CK: %s", DEVICE_KEY);
      client.println(strBuffer);
      client.println("Content-Type: application/json;charset=utf-8");
      client.print("Content-Length:");
      client.println(strlen(httpPayload));
      client.println();
      client.println(httpPayload);
      //Be sure to free memory dynamic allocated in function "generatehttpPayload()"
      free(httpPayload);
    }

    //client.println("[{\"id\":\"vSensor\",\"value\":[1,2,3]}]");


  }
}
