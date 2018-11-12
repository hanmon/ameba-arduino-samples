#include "Arduino.h"
#include "blinkLed.h"

void blinkLed(int pin, int duration, int count)
{	
	while(count>0)
	{
		digitalWrite(pin,HIGH);
		delay(duration);
		digitalWrite(pin,LOW);
		delay(duration);
		count--;
	}
}