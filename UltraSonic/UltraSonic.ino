/*
 * Measuring distance by HC-SR04 or US-100 connected with ameba arduino
 * Connecting trigger pin and echo pin to ameba pin12 and pin13
 * By Bruce Chiu
 */
const int trigPin=12;
const int echoPin=13;
float distance=0;
unsigned long duration=0;
void setup() {
  // put your setup code here, to run once:
  Serial.print(9600);
  //set trig an echo pin mode
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //send trigger pulse for 10us
  trigger();
  //measuring pulse width of high from echoPin
  duration=pulseIn(echoPin,HIGH); 
  distance=duration/58.0;
  Serial.println("Distance:"+String(distance)+" cm");
  delay(2000);
}

void trigger(){
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
}
  
