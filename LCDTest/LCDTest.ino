
void setup()
{
  initLCD();
//  lcd.setCursor(12, 1);
//  lcd.print("2");
  Serial.begin(9600);
}
void loop()
{ 
  clearLCD();
  printOnLCD("This is in Row 1",0);
  printOnLCD("This is in Row 2",1);
  Serial.println();
  delay(3000);
}
