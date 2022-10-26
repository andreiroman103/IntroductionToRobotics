const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int minAnalogValue = 0;
const int maxAnalogValue = 1023;
const int minLedIntensity = 0;
const int maxLedIntensity = 255;

int redAnalogValue;
int greenAnalogValue;
int blueAnalogValue;
int redValue;
int greenValue;
int blueValue;

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

/* the values for each potentiometer are read and stored in the according variable,
then the values are mapped from the analog value to the corresponding intensity value
and they are passed to the analogWrite function to be displayed by the led. */  
void loop() {
  redAnalogValue = analogRead(A2);
  greenAnalogValue = analogRead(A1);
  blueAnalogValue = analogRead(A0);

  redValue = map(redAnalogValue, minAnalogValue, maxAnalogValue, minLedIntensity, maxLedIntensity);
  greenValue = map(greenAnalogValue, minAnalogValue, maxAnalogValue, minLedIntensity, maxLedIntensity);
  blueValue = map(blueAnalogValue, minAnalogValue, maxAnalogValue, minLedIntensity, maxLedIntensity);

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
