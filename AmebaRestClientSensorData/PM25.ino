/*
  This example demonstrate how to read pm2.5 value on PMS 3003 air condition sensor

  PMS 3003 pin map is as follow:
    PIN1  :VCC, connect to 5V
    PIN2  :GND
    PIN3  :SET, 0:Standby mode, 1:operating mode
    PIN4  :RXD :Serial RX
    PIN5  :TXD :Serial TX
    PIN6  :RESET
    PIN7  :NC
    PIN8  :NC

  In this example, we only use Serial to get PM 2.5 value.

  The circuit: (BOARD RTL8195A)
   RX is digital pin 0 (connect to TX of PMS 3003)
   TX is digital pin 1 (connect to RX of PMS 3003)

*/

#include <SoftwareSerial.h>
#if defined(BOARD_RTL8195A)
SoftwareSerial mySerial(0, 1); // RX, TX
#elif defined(BOARD_RTL8710)
SoftwareSerial mySerial(17, 5); // RX, TX
#else
SoftwareSerial mySerial(0, 1); // RX, TX
#endif

#define pmsDataLen 32
uint8_t buf[pmsDataLen];
int idx = 0;


void initUART2() {
  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600
}

int* getPMValues() { // run over and over
  uint8_t c = 0;
  idx = 0;
  int pmValues[3];
  memset(buf, 0, pmsDataLen); //clear buf

  while (true) {
    while (c != 0x42) {
      while (!mySerial.available());
      c = mySerial.read();
    }
    while (!mySerial.available());
    c = mySerial.read();
    if (c == 0x4d) {
      // now we got a correct header)
      buf[idx++] = 0x42;
      buf[idx++] = 0x4d;
      break;
    }
  }

  while (idx != pmsDataLen) {
    while (!mySerial.available());
    buf[idx++] = mySerial.read();
  }

  pmValues[0] = ( buf[10] << 8 ) | buf[11]; //Value of PM1
  pmValues[1] = ( buf[12] << 8 ) | buf[13]; //Value of PM2.5
  pmValues[2] = ( buf[14] << 8 ) | buf[15]; //Value of PM10

  Serial.print("pm1: ");
  Serial.print(pmValues[0]);
  Serial.println(" ug/m3");
  Serial.print("pm2.5: ");
  Serial.print(pmValues[1]);
  Serial.println(" ug/m3");
  Serial.print("pm10: ");
  Serial.print(pmValues[2]);
  Serial.println(" ug/m3");
  return pmValues;
}

int getPM25() { // run over and over
  uint8_t c = 0;
  idx = 0;
  int pm10 = 0;
  int pm25 = 0;
  int pm100 = 0;
  memset(buf, 0, pmsDataLen); //clear buf

  while (true) {
    while (c != 0x42) {
      while (!mySerial.available());
      c = mySerial.read();
    }
    while (!mySerial.available());
    c = mySerial.read();
    if (c == 0x4d) {
      // now we got a correct header)
      buf[idx++] = 0x42;
      buf[idx++] = 0x4d;
      break;
    }
  }

  while (idx != pmsDataLen) {
    while (!mySerial.available());
    buf[idx++] = mySerial.read();
  }

  pm10 = ( buf[10] << 8 ) | buf[11];
  pm25 = ( buf[12] << 8 ) | buf[13];
  pm100 = ( buf[14] << 8 ) | buf[15];

  Serial.print("pm2.5: ");
  Serial.print(pm25);
  Serial.println(" ug/m3");
  return pm25;
}
