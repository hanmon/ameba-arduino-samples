const int redLedPin=13;
const int greenLedPin=12;

void setup() {
  // put your setup code here, to run once:
  pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);
}

void loop() {
  //Red Led first
  digitalWrite(redLedPin,HIGH);
  digitalWrite(greenLedPin,LOW);
  delay(1000);
  digitalWrite(redLedPin,LOW);
  digitalWrite(greenLedPin,HIGH);
  delay(1000);
  
  // put your main code here, to run repeatedly:

}
