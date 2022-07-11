# 1 "d:\\project\\ameba-arduino-samples\\SendDataToPC\\SendDataToPC.ino"
void setup()
{
  Serial.begin(115200);
  Serial.println("Example:SendDataToPC");
}

void loop()
{
  int value1 = random(0,100); //隨機給定三個任意數值
  int value2 = random(0,100);
  int value3 = random(0,100);

  Serial.print(value1,10);
  Serial.print(";");//每個數值以分號隔開
  Serial.print(value2,10);
  Serial.print(";");
  Serial.print(value3,10);
  Serial.print(";");
  Serial.println();
  delay(1000);
}
