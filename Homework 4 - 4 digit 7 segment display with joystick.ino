const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;
const int displayCount = 4;

const byte regSize = 8; 

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

int currentDisplayedDigits[displayCount] = { 
//0  1  2  3
  0, 0, 0, 0
};

const int encodingsNumber = 16;

const int joystickXPin = A0;
const int joystickYPin = A1;
const int joystickSWPin = 3;

int byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

int shortPressInterval = 50;
int longPressInterval = 1500;
int joystickXValue = 0;
int joystickYValue = 0;

int systemState = 1;
int currentDisplay = 0;
int currentNumberIndex = 0;

bool joystickMoved = false;
bool blink = false;

byte joystickSWValue = LOW;
byte longPressed = LOW;
byte joystickReading = LOW;
byte lastJoystickReading = HIGH;
byte joystickSWState = LOW;
byte lastJoystickSWValue = LOW;

const int minThreshold = 400;
const int maxThreshold = 600;

unsigned long lastDebounceTime = 0;
unsigned long blinkInterval = 300;
unsigned long previousBlink = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(joystickSWPin, INPUT_PULLUP);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
  }  
  reset();
}

void loop() {
  // read the joystick button value and use debounce to check if it's a long press or a short press
  joystickSWValue = digitalRead(joystickSWPin);
  if (joystickSWValue != lastJoystickSWValue) {
    lastDebounceTime = millis();
  } 
  if(millis() - lastDebounceTime > longPressInterval) {
    if(joystickSWValue != longPressed) {
      longPressed = joystickSWValue;
      if(longPressed == LOW) {
        reset();
      }
    }
  }
  else if (millis() - lastDebounceTime > shortPressInterval) {
    if (joystickSWValue != joystickSWState) {
      joystickSWState = joystickSWValue;
      if (joystickSWState == LOW) {
        systemState = 2;
      }
    }
  } 
  lastJoystickSWValue = joystickSWValue;

  // execute the function corresponding to the current system state 
  if (systemState == 1) {
    state1();
  }
  if (systemState == 2) {
    state2();
    blink = true;   
  }
}

void state1() {
  // dp blinking
  if (millis() - previousBlink >= blinkInterval){
    previousBlink = millis();
    blink = !blink;
  } 
  
  joystickYValue = analogRead(joystickYPin);  
  // right movement
  if (joystickYValue > maxThreshold && joystickMoved == false) {
    joystickMoved = true;
    if (currentDisplay < displayCount - 1) {
      currentDisplay++;
    }
  } 
  // left movement
  if (joystickYValue < minThreshold && joystickMoved == false)  {
    joystickMoved = true;
    if (currentDisplay > 0) {
      currentDisplay--;
    }
  }
  if (joystickYValue > minThreshold && joystickYValue < maxThreshold) {
    joystickReading = LOW;
  }
  if (joystickYValue < minThreshold || joystickYValue > maxThreshold) {
    joystickReading = HIGH;
  }
  if(joystickReading != lastJoystickReading) {
    lastDebounceTime = millis();
  }
  if(joystickReading != lastJoystickReading) {
    if(joystickReading == HIGH) {
      joystickMoved=false;
    }
  }
  lastJoystickReading = joystickReading;  
  currentNumberIndex = 0;
  writeNumber(blink);
}

void state2() {
  joystickXValue = analogRead(joystickXPin);
  // up movement
  if (joystickXValue > maxThreshold && joystickMoved == false) { 
    joystickMoved = true;
    if (currentNumberIndex < encodingsNumber - 1) {
      currentNumberIndex++;
      currentDisplayedDigits[currentDisplay] = currentNumberIndex;
    }        
  } 
  // down movement
  if (joystickXValue < minThreshold && joystickMoved == false) { 
    joystickMoved = true;
    if (currentNumberIndex > 0) {
      currentNumberIndex--;
      currentDisplayedDigits[currentDisplay] = currentNumberIndex;
    }        
  }
  if (joystickXValue > minThreshold && joystickXValue < maxThreshold) {
    joystickMoved = false;
  }  
  
  writeNumber(blink);
  
  // going back to state 1 when the joystick button is pressed
  joystickSWValue = digitalRead(joystickSWPin);
  if (joystickSWValue != lastJoystickSWValue) {
    lastDebounceTime = millis();
  } 
  if (millis() - lastDebounceTime > shortPressInterval) {
    if (joystickSWValue != joystickSWState) {
      joystickSWState = joystickSWValue;
      if (joystickSWState == LOW) {
        systemState = 1;
      }
    }
  }
  lastJoystickSWValue = joystickSWValue;
}

void reset() {
  for (int i = 0; i < displayCount; i++) {
    currentDisplayedDigits[i] = 0;
  } 
  currentDisplay = 0;
  systemState = 1;
}

void activateDisplay(byte displayNumber) {
  // turning off all the digits
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH); 
  } 
  // turning on the current digit
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeReg(byte encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}

void writeNumber(bool blink){ 
  int numberIndex;
  byte encoding;
  for(int i = 0; i <displayCount; i++) {  
    // turning off all the digits
    for (int i = 0; i < displayCount; i++) {
      digitalWrite(displayDigits[i], HIGH); 
    }  
    numberIndex = currentDisplayedDigits[i];
    encoding = byteEncodings[numberIndex];
    if (blink == true){
      if (i == currentDisplay){
        encoding = encoding + 1;
      }
    } 
    // changing the number
    writeReg(encoding);
    // activate the display
    activateDisplay(i);
    delay(3);
  }
}




























