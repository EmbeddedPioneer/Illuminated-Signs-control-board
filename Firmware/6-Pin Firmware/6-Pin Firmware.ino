/*
  Illuminated Signs Control Board - 06-Pin Version
  Developed by: EmbeddedPioneer
  Repository: https://github.com/EmbeddedPioneer/Illuminated-Signs-control-board/
  License: MIT

  Description:
  This firmware is designed for the Illuminated Signs Control Board to control up to 06 relays, 
  each corresponding to a LED segment in an illuminated sign.
  
  Features:
  - Supports 4 light patterns (Sequential Lighting, Wave effect, Reverse wave effect, and Random LED Lighting)
  - Controls the number of active LEDs using 4 DIP switches (1-06 LEDs)
  - Adjustable delay time (500ms or 1000ms)
  - 7 input buttons: 4 for LED count, 2 for mode selection, and 1 for delay time

  Hardware Requirements:
  - ATmega328P microcontroller
  - 12V/24V relays for LED control
  - Pull-up switches for mode and LED selection

*/

int relayPins[] = {6, 8, 7, 2, 1, 0}; 
int buttonPins[] = {5, 13, 12, 11, 9, A0, A1, A2}; 
int numberOfRelays = 6; 
int mode;           
int timeDelay;  
int Delay;  

void lightPattern1();
void lightPattern2();
void lightPattern3();
void lightPattern4();

void setup() {
  for (int i = 0; i < 12; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); 
  }
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
   pinMode(A5, INPUT);
}

void loop() {
  numberOfRelays = readRelayCount();
  mode = readMode();
  Delay = analogRead(A5);
  timeDelay= map(Delay, 0,  1023, 100, 1000);

  switch (mode) {
    case 0:
      lightPattern1();
      break;
    case 1:
      lightPattern2();
      break;
    case 2:
      lightPattern3();
      break;
    case 3:
      lightPattern4();
      break;
  }
}

// Reads the number of active relays based on switch inputs
int readRelayCount() {
  int count = 0;   
  if (digitalRead(buttonPins[0]) == LOW & digitalRead(buttonPins[1]) == HIGH & digitalRead(buttonPins[2]) == HIGH & digitalRead(buttonPins[3]) == HIGH){count=1;}
  if (digitalRead(buttonPins[0]) == HIGH & digitalRead(buttonPins[1]) == LOW & digitalRead(buttonPins[2]) == HIGH & digitalRead(buttonPins[3]) == HIGH){count=2;}  
  if (digitalRead(buttonPins[0]) == LOW & digitalRead(buttonPins[1]) == LOW & digitalRead(buttonPins[2]) == HIGH & digitalRead(buttonPins[3]) == HIGH){count=3;}
  if (digitalRead(buttonPins[0]) == HIGH & digitalRead(buttonPins[1]) == HIGH & digitalRead(buttonPins[2]) == LOW & digitalRead(buttonPins[3]) == HIGH){count=4;}  
  if (digitalRead(buttonPins[0]) == LOW & digitalRead(buttonPins[1]) == HIGH & digitalRead(buttonPins[2]) == LOW & digitalRead(buttonPins[3]) == HIGH){count=5;}
  if (digitalRead(buttonPins[0]) == HIGH & digitalRead(buttonPins[1]) == LOW & digitalRead(buttonPins[2]) == LOW & digitalRead(buttonPins[3]) == HIGH){count=6;}  
  return count;
}

// Reads the selected lighting mode based on button inputs
int readMode() {
  int mode = 0;
  if (digitalRead(buttonPins[4]) == LOW && digitalRead(buttonPins[5]) == LOW) { mode = 0; }
  if (digitalRead(buttonPins[4]) == LOW && digitalRead(buttonPins[5]) == HIGH) { mode = 1; }
  if (digitalRead(buttonPins[4]) == HIGH && digitalRead(buttonPins[5]) == LOW) { mode = 2; }
  if (digitalRead(buttonPins[4]) == HIGH && digitalRead(buttonPins[5]) == HIGH) { mode = 3; }
  return mode;
}

// Lighting pattern 1: Sequential activation
void lightPattern1() {
  for (int i = 0; i < numberOfRelays; i++) {
    digitalWrite(relayPins[i], LOW);  
    delay(timeDelay);
    digitalWrite(relayPins[i], HIGH);
  }
}

// Lighting pattern 2: Wave effect
void lightPattern2() {
  int b = numberOfRelays;
  for (int i = 0; i < numberOfRelays; i++) {
    for (int i = 0; i < b; i++) {
      digitalWrite(relayPins[i], LOW);  
      delay(timeDelay / 2);
      digitalWrite(relayPins[i], HIGH);
    }
    digitalWrite(relayPins[b - 1], LOW); 
    b--;
  }
}

// Lighting pattern 3: Reverse wave effect
void lightPattern3() {
  int C = numberOfRelays;
  for (int i = 0; i < numberOfRelays; i++) {
    for (int i = 0; i < C; i++) {
      digitalWrite(relayPins[i], LOW);  
      delay(timeDelay / 2);
      digitalWrite(relayPins[i], HIGH);
    }
    digitalWrite(relayPins[C - 1], LOW); 
    C--;
  }
}

// Lighting pattern 4: Random flashing
void lightPattern4() {
  for (int i = 0; i < numberOfRelays; i++) {
    int randRelay = random(0, numberOfRelays);
    digitalWrite(relayPins[randRelay], HIGH); 
    delay(timeDelay / 2);
    digitalWrite(relayPins[randRelay], LOW); 
  }
}

// Delay function for analog-based timing adjustment
void delay() {
  Delay = analogRead(A3);
  timeDelay = map(Delay, 0, 1023, 100, 1000);
  return;
}
