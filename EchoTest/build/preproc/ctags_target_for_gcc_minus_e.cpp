# 1 "d:\\project\\ameba-arduino-samples\\EchoTest\\EchoTest.ino"
void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(115200);
    Serial.println("A test for echo");
}
//
void loop()
{
}
void serialEvent()
{
    Serial.write(Serial.read());
}
