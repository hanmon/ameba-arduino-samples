//利用Serial.parseInt()接收多欄位int數值
int rx_buffer[3]; //宣告用來接收三個欄位數值的陣列
int i = 0;        //接收欄位的索引值

void setup()
{
    Serial.begin(115200);
    Serial.println("Example:RcvDataFromPC");
}

void loop()
{
    if (Serial.available() > 0)
    {
        for (i = 0; i < 3; i++)
        {
            rx_buffer[i] = Serial.parseInt(); //利用Serial.parseInt取出收到資料中的一個數值
        }
        //印出收到的數值
        for (i = 0; i < 3; i++)
        {
            if (rx_buffer[i] != 0)
            {
                Serial.print(rx_buffer[i]);
                Serial.print(";");
            }
        }
        Serial.println();
    }
}
