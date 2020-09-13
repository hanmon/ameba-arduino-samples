const int ledR=9;
void setup(){
    pinMode(ledR,OUTPUT);
    
}

void loop(){
    digitalWrite(ledR,HIGH);
    delay(500);
    digitalWrite(ledR,LOW);
    delay(500);
}