const int ledR=9;
void setup(){
    pinMode(ledR,OUTPUT);
    Serial.begin(115200);
    Serial.print("Hello World example for ameba arduino");
    
}

void loop(){
    digitalWrite(ledR,HIGH);
    delay(500);
    digitalWrite(ledR,LOW);
    delay(500);
}