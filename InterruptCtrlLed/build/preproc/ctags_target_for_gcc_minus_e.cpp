# 1 "d:\\project\\ameba-arduino-samples\\InterruptCtrlLed\\InterruptCtrlLed.ino"
int button = 3;
int led = 9;

int ledState = 1;

void button_handler(uint32_t id, uint32_t event) {
  if (ledState == 0) {
    // turn on LED
    ledState = 1;
    digitalWrite(led, ledState);
  } else {
    // turn off LED
    ledState = 0;
    digitalWrite(led, ledState);
  }
}

void setup() {
  pinMode(led, 0x01);
  digitalWrite(led, ledState);

  pinMode(button, 0x06);
  digitalSetIrqHandler(button, button_handler);
}

void loop() {
  delay(1000);
}
