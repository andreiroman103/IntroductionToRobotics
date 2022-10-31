const int buzzerPin = 12;
const int buttonPin = 4;
const int redCarLightPin = 11;
const int yellowCarLightPin = 10;
const int greenCarLightPin = 9;
const int redPedestrianLightPin = 6;
const int greenPedestrianLightPin = 5;

byte buttonValueRead = LOW;
byte lastButtonValueRead = LOW;
byte buttonState = LOW;
byte greenPedestrianLightValue;

unsigned long lastDebounceTime = 0;
unsigned long timeWhenButtonWasPressed;
unsigned long timeState2Started;
unsigned long timeState3Started;
unsigned long timeState4Started;
unsigned long state3Interval = 1500;
unsigned long state4Interval = 400;
unsigned long previousTimeBuzzerOn;
unsigned long previousBlinkAndBuzz;

unsigned int debounceDelay = 50;
unsigned int state2Countdown = 8000;
unsigned int state2Duration = 3000;
unsigned int state3Duration = 8000;
unsigned int state4Duration = 4000;

int buttonPressCount = 0;
int systemState = 1;
int state3BuzzerFrequency = 900;
int state3BuzzerDuration = 400;
int state4BuzzerFrequency = 500;
int state4BuzzerDuration = 150;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redCarLightPin, OUTPUT);
  pinMode(yellowCarLightPin, OUTPUT);
  pinMode(greenCarLightPin, OUTPUT);
  pinMode(redPedestrianLightPin, OUTPUT);
  pinMode(redPedestrianLightPin, OUTPUT);
}

void loop() {
  if (systemState == 1){
    defaultState();
  }
  
  if(systemState == 2) {
    state2();
  }
  
  if (systemState == 3) {
    state3();
  }

  if (systemState == 4) {
    state4();   
  }   
}

/* green light for cars, red light for pedestrians. 
Duration is indefinite and the default state is changed by
pressing the button. */
void defaultState() {
    digitalWrite(greenCarLightPin, HIGH);
    digitalWrite(redPedestrianLightPin, HIGH);
    digitalWrite(redCarLightPin, LOW);
    digitalWrite(greenPedestrianLightPin, LOW);
    buttonValueRead = digitalRead(buttonPin); 
  
  // I used debounce to make sure the button press is registered correctly
  if (buttonValueRead != lastButtonValueRead) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime > debounceDelay) && systemState == 1) {
    if (buttonValueRead != buttonState) {
      buttonState = buttonValueRead;
      if (buttonState == LOW) {
        systemState = 2;
        timeWhenButtonWasPressed = millis();
      }
    }
  }
  lastButtonValueRead = buttonValueRead;
}

/* yellow light for cars, red light for pedestrians.
Duration: 3 seconds, state 2 starts after 8 seconds since the button was pressed.
The duration and the countdown are controlled by the variables state2Countdown and
state2Duration, respectively. */
void state2() {
  if (millis() - timeWhenButtonWasPressed > state2Countdown) {
    timeState2Started = timeWhenButtonWasPressed + state2Countdown;        
    digitalWrite(yellowCarLightPin, HIGH);
    digitalWrite(redPedestrianLightPin, HIGH);  
    digitalWrite(greenCarLightPin, LOW);
    if (millis() - timeState2Started > state2Duration) {
      systemState = 3;
    }
  }
}

/* red light for cars, green light for pedestrians and beeping sound from the buzzer at a constant interval.
Duration: 8 seconds, state 3 starts after state 2 ends.
The frequency and duration of the beeping sound are controlled by the variables state3BuzzerFrequency 
and state3BuzzerDuration, and the interval is controlled by state3Interval. */
void state3() {
  timeState3Started = timeWhenButtonWasPressed + state2Countdown + state2Duration;
  digitalWrite(redCarLightPin, HIGH);
  digitalWrite(greenPedestrianLightPin, HIGH);
  digitalWrite(yellowCarLightPin, LOW);
  digitalWrite(redPedestrianLightPin, LOW);
  if (millis() - previousTimeBuzzerOn > state3Interval) {
    previousTimeBuzzerOn = millis();
    tone(buzzerPin, state3BuzzerFrequency, state3BuzzerDuration);
  }
  if (millis() - timeState3Started > state3Duration) {
    systemState = 4;
  }
}

/* red light for cars, blinking green light for pedestrians and a faster beeping sound from the buzzer.
Duration: 4 seconds, state 4 starts after state 3 ends.
The frequency and duration of the beeping sound are controlled by the variables state4BuzzerFrequency 
and state4BuzzerDuration, and the interval is controlled by state4Interval.
After state 4, the system goes back to the default state. */
void state4() {
  timeState4Started = timeWhenButtonWasPressed + state2Countdown + state2Duration + state3Duration;  
  digitalWrite(redCarLightPin, HIGH);  
  if (millis() - previousBlinkAndBuzz > state4Interval) {
    previousBlinkAndBuzz = millis();
    
    if (greenPedestrianLightValue == LOW) {
      greenPedestrianLightValue = HIGH;
    }
    else {
      greenPedestrianLightValue = LOW;
    }    
    digitalWrite(greenPedestrianLightPin, greenPedestrianLightValue);
    
    tone(buzzerPin, state4BuzzerFrequency, state4BuzzerDuration);
  }
  if (millis() - timeState4Started > state4Duration) {
    systemState = 1;
  } 
}
