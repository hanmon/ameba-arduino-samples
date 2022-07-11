# 1 "d:\\project\\ameba-arduino-samples\\BtnLibraryTest\\BtnLibraryTest.ino"
# 2 "d:\\project\\ameba-arduino-samples\\BtnLibraryTest\\BtnLibraryTest.ino" 2
Button button(3);
const int ledR=9;
bool ledState=0x0;
void setup()
{
 button.begin();
    Serial.begin(115200);
    pinMode(ledR,0x01);
}

void loop()
{
 if(button.pressed()){
        Serial.println("Button Pressed");
        ledState=!ledState;
        digitalWrite(ledR,ledState);
    }

}
