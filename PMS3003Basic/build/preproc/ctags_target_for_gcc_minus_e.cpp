# 1 "d:\\project\\ameba-arduino-samples\\PMS3003Basic\\PMS3003Basic.ino"
# 2 "d:\\project\\ameba-arduino-samples\\PMS3003Basic\\PMS3003Basic.ino" 2
# 3 "d:\\project\\ameba-arduino-samples\\PMS3003Basic\\PMS3003Basic.ino" 2

SoftwareSerial mySerial(0,1);
PMS pms(mySerial);
PMS::DATA data;

void setup()
{
  Serial.begin(115200); // for log UART
  mySerial.begin(9600); // for interfacing PMS5003
}

void loop()
{
  if (pms.read(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();
  }
}
