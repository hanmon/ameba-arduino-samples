#include <Arduino.h>
#line 1 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
/*
   Three ways of polling for button pushed event to toggle led.
   The circuit:
   1.A push button is attached to D3 with pull down resistor.
   2.An led is attached to D9 with a resistor in series.
   Created 2019-08-30
   Author: Bruce Chiu
   Mail: boo.chiu@gmail.com
*/

const byte btnPin = 3;
const byte ledPin = 9;
const int debounceTime = 20;//設定除跳時間

#line 15 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
void setup();
#line 22 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
void toggleLED();
#line 27 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
void loop();
#line 36 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
void debounceMethodOne();
#line 50 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
void debounceMethodTwo();
#line 67 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
void debounceMethodThree();
#line 15 "d:\\project\\ameba-arduino-samples\\BtnPolling\\BtnPolling.ino"
void setup() {
  pinMode(btnPin, INPUT);//設定按鍵腳位為輸入
  pinMode(ledPin, OUTPUT);//設定LED腳位為輸出
  Serial.begin(115200);//設定序列埠速率
  Serial.println("Button pressed detection");//印出提示字串
}

void toggleLED() {
  static boolean ledState = LOW;//宣告static變數以儲存led狀態
  digitalWrite(ledPin, ledState ^= 1);//將ledState狀態變換後作為digitalWrite的輸出狀態
}

void loop() {
  //選擇以下任一種輪詢的方式
  debounceMethodOne();
  //debounceMethodTwo();
  //debounceMethodThree();
}



void debounceMethodOne() {
  static boolean lastBtnState = LOW;//宣告static boolean變數以儲存最新的按鍵偵測狀態
  if (lastBtnState!=digitalRead(btnPin)) {//若狀態有變遷
    delay(debounceTime);//則開始除跳
    if (lastBtnState!=digitalRead(btnPin)) {//若除跳後狀態維持
      lastBtnState = digitalRead(btnPin);//更新按鍵偵測狀態
      if (lastBtnState == LOW) {//若按鍵偵測狀態為LOW，代表使用者按下按鍵又放開，因此判定為一次按下事件
        toggleLED();//切換LED燈狀態
        Serial.println("Led Toggled");
      }
    }
  }
}

void debounceMethodTwo() {
  static boolean lastBtnState = LOW;//宣告static boolean變數以儲存最新的按鍵偵測狀態
  if (lastBtnState != digitalRead(btnPin)) {//若狀態有變遷
    lastBtnState = digitalRead(btnPin);//更新按鍵偵測狀態
    for (int count = 0; count < 10; count++) {//開始除跳
      delay(1);
      if (lastBtnState != digitalRead(btnPin)) {//除跳中，若有狀態變遷，則再延長除跳時間
        count = 0;
      }
    }
    if (lastBtnState == LOW) {//除跳結束，若按鍵偵測狀態為LOW，代表使用者按下按鍵又放開，因此判定為一次按下事件
      toggleLED();//切換LED燈狀態
      Serial.println("Led Toggled");
    }
  }
}

void debounceMethodThree() {
  static int stateChageCount = 0;//宣告int變數以儲存按鍵偵測狀態變遷的次數
  static boolean lastBtnState = LOW;//宣告static boolean變數以儲存最新的按鍵偵測狀態
  if (lastBtnState != digitalRead(btnPin)) {//若狀態有變遷
    lastBtnState = digitalRead(btnPin);//更新按鍵偵測狀態
    //開始除跳
    delay(debounceTime);
    if (lastBtnState == digitalRead(btnPin)) {//若狀態維持
      stateChageCount++;//狀態變遷的次數累加
    }
  }
  if (stateChageCount == 2) {//狀態變遷的次數累加為2，則代表使用者按下按鍵又放開，因此判定為一次按下事件
    toggleLED();//切換LED燈狀態
    Serial.println("Led Toggled");
    stateChageCount = 0;//清除狀態變遷的計數值
  }
}

