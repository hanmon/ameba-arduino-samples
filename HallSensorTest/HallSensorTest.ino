int ledR = 9;//LED pin
int sensor = 4; //sensor pin
int val; //numeric variable

void setup()
{
	pinMode(ledR, OUTPUT); //set LED pin as output
	pinMode(sensor, INPUT); //set sensor pin as input
}

void loop()
{
	val = digitalRead(sensor); //Read the sensor
	if(val == LOW) //when magnetic field is detected, turn led on
	{
		digitalWrite(ledR, LOW);
	}
	else
	{
		digitalWrite(ledR, HIGH);
	}
}