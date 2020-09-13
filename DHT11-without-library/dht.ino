
struct {
  float temperature;
  float humidity;
} dhtSensorValues;
unsigned long maxCycles = microsecondsToClockCycles(1000);
byte data[5];
unsigned long cycles[80];
const unsigned long timeoutValue = 1000000;

boolean getDHTSensorValues(int dhtPin) {
  unsigned long triggerTime;
  pinMode(dhtPin, INPUT_PULLUP);
  //  digitalWrite(dhtPin, HIGH);
  delay(250);
  pinMode(dhtPin, OUTPUT);
  digitalWrite(dhtPin, LOW);
  delay(20);
  pinMode(dhtPin, INPUT_PULLUP);
  //delayMicroseconds(25);
  //  triggerTime = millis();

  delayMicroseconds(10);
  unsigned long pulse1, pulse2;
  pulse1 = expectPulse(dhtPin, LOW);

  pulse2 = expectPulse(dhtPin, HIGH);

  if (pulse1 == 0 || pulse2 == 0) {
    return 0;
  };
  //  Serial.print("pulse1="+String(pulse1));
  //  Serial.print("pulse2="+String(pulse2));
  //  Serial.println("read pulse width and store");
  //read pulse width and store
  for (int i = 0; i < 80; i += 2) {
    cycles[i]   = expectPulse(dhtPin, LOW);
    cycles[i + 1] = expectPulse(dhtPin, HIGH);

    //    if(cycles[i]==0 || cycles[i + 1] ==0){
    //      return 0;
    //    }
  }
  Serial.println("pulse1=" + String(pulse1));
  Serial.println("pulse2=" + String(pulse2));
  for (int i = 0; i < 80; i += 2) {
    Serial.print("cycles[" + String(i) + "]=");
    Serial.println(cycles[i]);
    Serial.print("cycles[" + String(i + 1) + "]=");
    Serial.println(cycles[i + 1]);
    Serial.println("check each bit and store value in data");
  }
  //check each bit and store value in data
  for (int i = 0; i < 40; i++) {
    unsigned long lowCycle = cycles[i * 2];
    unsigned long highCycle = cycles[i * 2 + 1];
    if (lowCycle == 0 || highCycle == 0) {
      return 0;
    }
    data[i / 8] <<= 1;
    if (lowCycle < highCycle) {
      data[i / 8] |= 1;
    }
  }
  for (int i = 0; i < 5; i++) {
    Serial.print("data[" + String(i) + "]=");
    Serial.println(data[i]);
  }
  //verifying checksum
  if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
    Serial.println("DHT checksum succeeded!");
    return 1;
  }
  else {
    Serial.println("DHT checksum failure!");
    return 0;
  }

}


unsigned long expectPulse(int pin, boolean level) {
  unsigned long count = 0;
  while (digitalRead(pin) == level) {
    if (count++ > maxCycles) {
      return 0;
    }
  }
  return count;
}

float readHumidity() {
  float f = NAN;

  f = data[0] + data[1] * 0.1;

  return f;
}

float readTemperature() {
  float f = NAN;
  f = data[2];
  if (data[3] & 0x80) {
    f = -1 - f ;
  }
  f += (data[3] & 0x0f) * 0.1;
  return f;
}
