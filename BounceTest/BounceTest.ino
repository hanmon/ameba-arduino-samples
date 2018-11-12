const int extIntPin = 3; //for interuppt0
volatile int count = 0;
void setup() {
  Serial.begin(9600);
  pinMode(extIntPin, INPUT_PULLUP);
  attachInterrupt(0, analyze, CHANGE); //第一個參數表示使用int 0(Pin2)
}
void loop() {
  delay(3000);
  Serial.print("Count of levle change in 3 seconds:");
  Serial.println(count);
  count = 0;
}

void analyze() {
  count++;
}
