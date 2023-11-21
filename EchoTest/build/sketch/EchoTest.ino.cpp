#include <Arduino.h>
#line 1 "D:\\project\\ameba-arduino-samples\\EchoTest\\EchoTest.ino"
#line 1 "D:\\project\\ameba-arduino-samples\\EchoTest\\EchoTest.ino"
void setup();
#line 8 "D:\\project\\ameba-arduino-samples\\EchoTest\\EchoTest.ino"
void loop();
#line 11 "D:\\project\\ameba-arduino-samples\\EchoTest\\EchoTest.ino"
void serialEvent();
#line 1 "D:\\project\\ameba-arduino-samples\\EchoTest\\EchoTest.ino"
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
