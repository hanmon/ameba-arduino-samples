#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\PMS3003Basic\\PMS3003Basic.ino"
#include "PMS.h"
#include "SoftwareSerial.h"

SoftwareSerial mySerial(0,1);
PMS pms(mySerial);
PMS::DATA data;

#line 8 "d:\\project\\ameba-arduino-samples\\PMS3003Basic\\PMS3003Basic.ino"
void setup();
#line 14 "d:\\project\\ameba-arduino-samples\\PMS3003Basic\\PMS3003Basic.ino"
void loop();
#line 8 "d:\\project\\ameba-arduino-samples\\PMS3003Basic\\PMS3003Basic.ino"
void setup()
{
  Serial.begin(115200);   // for log UART
  mySerial.begin(9600);  // for interfacing PMS5003
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


