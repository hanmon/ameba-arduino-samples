/*
   Measuring ambient light by light dependent resistor module connected with ameba arduino and printing on I2C LCD
   Connecting A0 to ameba pin A0
   Connecting DO to ameba pin D14
   By Bruce Chiu
*/

const int ldrPin = A0;
const int doPin = 14;
// declare red led pin number
const int redPin = 9;
int analogValue = 0;
// strong light:160, general:260~300 ,weak light:600
int upperBound = 460, lowerBound = 400;
float lastTime = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  analogValue = analogRead(ldrPin);
  if (analogValue > upperBound)
  { // weak light turn on the light
    digitalWrite(redPin, LOW);
  }
  else if (analogValue < lowerBound) // Strong Light
  {
    //Strong Light,turn off the light
    digitalWrite(redPin, HIGH);
  }
  if ((millis() - lastTime) > 2000)
  {
    Serial.println("Analog Value:");
    Serial.println(analogValue);
    lastTime = millis();
  }
}
