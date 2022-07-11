# 1 "d:\\project\\ameba-arduino-samples\\MicrophoneTest2\\MicrophoneTest2.ino"
// Declaration and initialization of the input pin
int Analog_Eingang = 1; // X-axis-signal
int Digital_Eingang = 4; // Button

void setup ()
{
  pinMode (Analog_Eingang, 0x00);
  pinMode (Digital_Eingang, 0x00);

  Serial.begin (115200); // Serial output with 9600 bps
}

// The program reads the current value of the input pins
// and outputs it via serial out
void loop ()
{
  float Analog;
  int Digital;

  // Current value will be read and converted to voltage 
  Analog = analogRead (Analog_Eingang) * (3.3/ 1023.0);
  Digital = digitalRead (Digital_Eingang);

  //... and outputted here
  Serial.print ("Analog voltage value:"); Serial.print (Analog, 4); Serial.print ("V, ");
  Serial.print ("Extreme value:");

  if(Digital==1)
  {
      Serial.println (" reached");
  }
  else
  {
      Serial.println (" not reached yet");
  }
  Serial.println ("----------------------------------------------------------------");
  delay (200);
}
