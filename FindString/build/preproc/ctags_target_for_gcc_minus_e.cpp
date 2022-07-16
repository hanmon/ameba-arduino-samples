# 1 "d:\\project\\ameba-arduino-samples\\FindString\\FindString.ino"
char targetString[] = "chtti";
void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(115200);
    Serial.println("A test for \"find\"");
}
void loop()
{

}
void serialEvent()
{
    while (Serial.available() > 0) //收到資料
        {
            if (Serial.find(targetString))
            {
                Serial.print("Target string:");
                Serial.print(targetString);
                Serial.println(" found!");
            }
        }
}
