const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

const int joystickXPin = A0;
const int joystickYPin = A1;
const int joystickSWPin = 12;

const int minThreshold = 400;
const int maxThreshold = 600;
const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;
const int segmentSize = 8;
const int directions = 4;

bool commonAnode = false;
bool joystickMoved = false;

unsigned long lastDebounceTime = 0;
unsigned long lastTimeLong = 0; 
unsigned long lastJoyTime = 0;
unsigned long blinkInterval = 300;
unsigned long previousBlink = 0;

int systemState = 1;
int currentSegment = segmentSize - 1;
int lastSegment = segmentSize - 1;
int shortPressInterval = 50;
int longPressInterval = 1500;
int joystickXValue = 0;
int joystickYValue = 0;
int nextSegment = 0;

byte joystickSWValue = LOW;
byte lastJoystickSWValue = LOW;
byte joystickReading = LOW;
byte lastJoystickReading = HIGH;
byte longPressed = LOW;
byte segmentState = LOW;
byte dpState = LOW;
byte joystickSWState = LOW;

int segments[segmentSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int segmentsStates[segmentSize] = {
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

int possibleMovements[segmentSize][directions] = {
//   up down left right (-1 -> None)
    {-1, 6, 5, 1},      //a -> 0
    { 0, 6, 5,-1},      //b -> 1
    { 6, 3, 4, 7},      //c -> 2
    { 6,-1, 4, 2},      //d -> 3
    { 6, 3,-1, 2},      //e -> 4
    { 0, 6,-1, 1},      //f -> 5
    { 0, 3,-1,-1},      //g -> 6
    {-1,-1, 2,-1}       //dp -> 7 
};

void setup() {
  for (int i = 0; i < segmentSize; i++) {
  pinMode(segments[i], OUTPUT);
  }
  pinMode(joystickSWPin, INPUT_PULLUP);
  if (commonAnode == true) {
    segmentState = !segmentState;
  }
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
  }
}

void reset(){
  // turns off all of the segments, updates the values in the segment states vector and sets the current segment back to the DP segment
  for (int i = 0; i < segmentSize; i++) {
    digitalWrite(segments[i], LOW);
  }
  for (int i = 0; i < segmentSize; i++) {
    segmentsStates[i] = LOW;
  }
  currentSegment = segmentSize - 1;
  systemState = 1;
}

void changeSegment(int direction) {
  // changes the segment based on the possibleMovements matrix and the direction parameter
  // if the matrix value for the next segment is not -1 (the next segment is reachable from the current segment), the next segment becomes the current segment
  nextSegment = possibleMovements[currentSegment][direction];
  if (nextSegment != -1) {
    lastSegment = currentSegment;
    currentSegment = nextSegment; 
    digitalWrite(segments[lastSegment],segmentsStates[lastSegment]);
  }
}

void state1() {
  // current segment is blinking
  if (millis() - previousBlink >= blinkInterval){
    previousBlink = millis();
    segmentState = !segmentState;
    digitalWrite(segments[currentSegment], segmentState);
  }    

  // getting the direction of the movement from the joystick
  joystickXValue = analogRead(joystickXPin);
  joystickYValue = analogRead(joystickYPin);
  // up movement
  if (joystickXValue > maxThreshold && joystickMoved == false) {
    joystickMoved = true;
    changeSegment(up);      
  } 
  // down movement      
  if (joystickXValue < minThreshold && joystickMoved == false) {
    joystickMoved = true;
    changeSegment(down);
  }
  // right movement
  if (joystickYValue > maxThreshold && joystickMoved == false) {
    joystickMoved = true;
    changeSegment(right);
  } 
  // left movement
  if (joystickYValue < minThreshold && joystickMoved == false)  {
    joystickMoved = true;
    changeSegment(left);
  }      
  if ((joystickXValue > minThreshold && joystickXValue < maxThreshold) || (joystickYValue > minThreshold && joystickYValue < maxThreshold)) {
    joystickReading = LOW;   
  }
  if((joystickXValue < minThreshold || joystickXValue > maxThreshold) || (joystickYValue < minThreshold || joystickYValue > maxThreshold)) {
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
}

void state2() { 
  // setting the previous state to the current segment
  digitalWrite(segments[currentSegment], segmentsStates[currentSegment]);    

  // changing the state of the segment using the X-axis of the joystick (which translates to the up and down movement in this case)
  joystickXValue = analogRead(joystickXPin);
  // up movement
  if (joystickXValue > maxThreshold && joystickMoved == false) { 
    joystickMoved = true;
    segmentsStates[currentSegment] = HIGH; 
    digitalWrite(segments[currentSegment],segmentsStates[currentSegment]);       
  } 
  // down movement
  if (joystickXValue < minThreshold && joystickMoved == false) { 
    joystickMoved = true;
    segmentsStates[currentSegment] = LOW; 
    digitalWrite(segments[currentSegment],segmentsStates[currentSegment]);        
  }
  if (joystickXValue > minThreshold && joystickXValue < maxThreshold) {
    joystickMoved = false;
  }

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
