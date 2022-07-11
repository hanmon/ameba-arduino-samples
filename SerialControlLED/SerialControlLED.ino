//由 serial 指令控制 LED亮滅，收到 ' 時點亮 LED ，收到 ‘ 時熄滅 LED
const int ledPin = 9; // the pin that the LED is attached to
int incomingByte;     // a variable to read incoming serial data into
void setup()
{
    // initialize serial communication:
    Serial.begin(115200);
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
}
void loop()
{
    //檢查是否有收到到的序列埠資料
    if (Serial.available() > 0)
    {
        incomingByte = Serial.read(); // read the oldest byte in the serial buffer:
        Serial.println((char)incomingByte);
        //若收到大寫 ' H'，點亮 LED 
        if (incomingByte == 'H')
        {
            digitalWrite(ledPin, HIGH);
        }
        //若收到大寫 ' H'，關閉 LED 
        if (incomingByte == 'L')
        {
            digitalWrite(ledPin, LOW);
        }
    }
}