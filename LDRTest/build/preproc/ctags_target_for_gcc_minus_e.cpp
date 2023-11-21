# 1 "d:\\project\\ameba-arduino-samples\\LDRTest\\LDRTest.ino"
/*

   Measuring ambient light by light dependent resistor module connected with ameba arduino and printing on I2C LCD

   Connecting A0 to ameba pin A0

   Connecting DO to ameba pin D14

   By Bruce Chiu

*/
# 9 "d:\\project\\ameba-arduino-samples\\LDRTest\\LDRTest.ino"
const int ldrPin=1;
const int doPin=14;
int analogValue=0,prevAnalogValue=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogValue=analogRead(ldrPin);
  Serial.println("Analog Value:");
  Serial.println(analogValue);
  delay(2000);
}
