# 1 "d:\\project\\ameba-arduino-samples\\HelloWorld\\HelloWorld.ino"
const int ledR=9;
void setup(){
    pinMode(ledR,0x01);
    Serial.begin(115200);
    Serial.print("Hello World example for ameba arduino");

}

void loop(){
    digitalWrite(ledR,0x1);
    delay(500);
    digitalWrite(ledR,0x0);
    delay(500);
}
