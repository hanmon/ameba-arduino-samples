# 1 "d:\\project\\ameba-arduino-samples\\UltraSonic\\UltraSonic.ino"
/*

 * Measuring distance by HC-SR04 or US-100 connected with ameba arduino

 * Connecting trigger pin and echo pin to ameba pin12 and pin13, buzzer pin to pin8

 * By Bruce Chiu

 */
# 6 "d:\\project\\ameba-arduino-samples\\UltraSonic\\UltraSonic.ino"
const int trigPin=12;
const int echoPin=13,buzzerPin=8;
float distance=0;
unsigned long duration=0;
unsigned int wait=0;
void setup() {
  // put your setup code here, to run once:
  Serial.print(115200);
  //set trig an echo pin mode
  pinMode(trigPin,0x01);
  pinMode(echoPin,0x00);
}

void loop() {
  // put your main code here, to run repeatedly:
  //send trigger pulse for 10us
  trigger();
  //measuring pulse width of high from echoPin
  duration=pulseIn(echoPin,0x1);
  distance=duration/58.0;
  Serial.println("Distance:"+String(distance)+" cm");
  wait=map(distance,0,500,100,1000);
  wait=((wait)<(0)?(0):((wait)>(1000)?(1000):(wait)));
  tone(buzzerPin,1500,wait);
  delay(wait*2);
}

void trigger(){
  digitalWrite(trigPin,0x1);
  delayMicroseconds(10);
  digitalWrite(trigPin,0x0);
}
