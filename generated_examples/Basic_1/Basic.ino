#include "PMS.h"
#include "SoftwareSerial.h"


PMS pms(Serial1);
PMS::DATA data;

void setup()
{
  Serial.begin(115200);   // UART1 (Initializing Log UART)
  Serial1.begin(9600);  // UART0 (Interfacing PMS5003)
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

  // Do other stuff...
}