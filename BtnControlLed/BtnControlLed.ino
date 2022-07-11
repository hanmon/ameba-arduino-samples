/*
   Simple button controlled led
   The circuit:
   1.A push button is attached to D2 with pull down resistor.
   2.An led is attached to D8 with a resistor in series.
   Created 2019-08-30
   Author: Bruce Chiu
   Mail: boo.chiu@gmail.com
*/
//D3外接下拉電阻，為正向邏輯的電路，D9外接LED並串上適當的電阻，或使用模組
const byte btnPin = 3;// 按鈕連接在D3，正向邏輯
const byte ledPin = 9;// LED 連接在D9
bool btnState = LOW; //存放讀取值的bool變數

void setup() {
  Serial.begin(115200);
  Serial.print("Example:BtnControlLed");
  pinMode(btnPin, INPUT);   //設定D3為輸入
  pinMode(ledPin, OUTPUT);  //設定D9為輸出
}

void loop() {
  btnState = digitalRead(btnPin);   // 讀取輸入腳位
  digitalWrite(ledPin, !btnState);  // 依據輸入腳位的狀態設定LED狀態
}
