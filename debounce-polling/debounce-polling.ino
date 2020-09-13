int btnPin = 3;
int ledPin = 2;
int debounceTime = 40;
boolean ledState = LOW;
boolean lastBtnState = LOW;
boolean btnState = LOW;
int stateChageCount = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Button pressed detection");
}

void loop() {
  // put your main code here, to run repeatedly:
  debounceMethodOne();
  //debounceMethodTwo();
  // debounceMethodThree();
}

void debounceMethodOne() {
  if (lastBtnState != digitalRead(btnPin)) {
    lastBtnState = digitalRead(btnPin);
    //start debouncing
    delay(debounceTime);

    if (lastBtnState == digitalRead(btnPin))
      stateChageCount++;
  }
  if (stateChageCount == 2) {
    toggleLED();
    Serial.println("Led Toggled");
    stateChageCount = 0;
  }
}

void debounceMethodTwo() {
  boolean reading = digitalRead(btnPin);
  if (reading != lastBtnState) {
    delay(debounceTime);
    if (reading != btnState) {
      btnState = reading;
      if (btnState == LOW) {
        toggleLED();
        Serial.println("Led Toggled");
      }
    }
  }
  lastBtnState = reading;
}

void debounceMethodThree() {
  if (lastBtnState != digitalRead(btnPin)) {
    lastBtnState = digitalRead(btnPin);
    //start debouncing
    for (int count = 0; count < 10; count++) {
      delay(1);
      if (lastBtnState != digitalRead(btnPin)) {
        count = 0;
      }
    }
    if (lastBtnState == HIGH) {
      toggleLED();
      Serial.println("Led Toggled");
    }
  }
}

void toggleLED() {
  digitalWrite(ledPin, ledState ^= 1);
}
