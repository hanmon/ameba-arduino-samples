const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
#define COMMON_ANODE

void setColor(int red, int green, int blue) {
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setColor(unsigned long rgbColor) {
  int red, green, blue;
  red = (rgbColor & 0xFF0000) >> 16;
  green = (rgbColor& 0xFF00) >> 8;
  blue = rgbColor & 0xFF;
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

