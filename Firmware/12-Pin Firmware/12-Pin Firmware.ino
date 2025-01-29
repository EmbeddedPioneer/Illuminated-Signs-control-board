/*
  Illuminated Signs Control Board - 12-Pin Version
  Developed by: EmbeddedPioneer
  Repository: https://github.com/EmbeddedPioneer/Illuminated-Signs-control-board/
  License: MIT

  Description:
  This firmware is designed for the Illuminated Signs Control Board to control up to 12 relays, 
  each corresponding to a LED segment in an illuminated sign.
  
  Features:
  - Supports 4 light patterns (Static, Sequential, Blinking, and Random)
  - Controls the number of active LEDs using 4 DIP switches (1-12 LEDs)
  - Adjustable delay time (500ms or 1000ms)
  - 7 input buttons: 4 for LED count, 2 for mode selection, and 1 for delay time

  Hardware Requirements:
  - ATmega328P microcontroller
  - 12V/24V relays for LED control
  - Pull-up switches for mode and LED selection

*/

int relayPins[] = {5, 4, 3, 2, 0, 1, A5, A4, A3, A2, A1, A0}; // Relay control pins
int buttonPins[] = {6, 7, 8, 9, 10, 11, 12}; // Switch buttons for settings
int numberOfRelays = 0; // Number of active LEDs (set by switches)
int mode = 0;           // Light mode (selected using 2 switches)
int timeDelay = 500;     // Delay time (selected using 1 switch)

// Function prototypes
void lightPattern1(); // Sequential Lighting
void lightPattern2(); // Blinking All LEDs
void lightPattern3(); // Alternate Pairs Lighting
void lightPattern4(); // Random LED Lighting

void setup() {
  // Set relay pins as output and turn them off initially
  for (int i = 0; i < 12; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Relays are active-low
  }

  // Set button pins as input with internal pull-up resistors
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  numberOfRelays = readRelayCount(); // Read number of LEDs to control
  mode = readMode(); // Read operation mode
  timeDelay = digitalRead(buttonPins[6]) == LOW ? 500 : 1000; // Set delay time

  // Execute the selected light pattern
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

/*
  Reads the number of LEDs to control (1-12).
  The 4 switches represent a binary value (0000 to 1100).
*/
int readRelayCount() {
  int count = 0;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) { // LOW means switch is ON
      count |= (1 << i);
    }
  }
  return count;
}

/*
  Reads the selected lighting mode (0 to 3).
  The 2 switches define the mode in binary (00, 01, 10, 11).
*/
int readMode() {
  int mode = 0;
  if (digitalRead(buttonPins[4]) == LOW) { // First mode switch
    mode |= 1; 
  }
  if (digitalRead(buttonPins[5]) == LOW) { // Second mode switch
    mode |= 2; 
  }
  return mode;
}

/*
  Pattern 1: Sequential Lighting
  - LEDs turn ON one by one, then OFF in the same order.
*/
void lightPattern1() {
  for (int i = 0; i < numberOfRelays; i++) {
    digitalWrite(relayPins[i], LOW);  
    delay(timeDelay);
    digitalWrite(relayPins[i], HIGH);
  }
}

/*
  Pattern 2: Blinking All LEDs
  - All LEDs turn ON at the same time, then turn OFF together.
*/
void lightPattern2() {
  for (int i = 0; i < numberOfRelays; i++) {
    digitalWrite(relayPins[i], LOW);  
  }
  delay(timeDelay);
  for (int i = 0; i < numberOfRelays; i++) {
    digitalWrite(relayPins[i], HIGH); 
  }
}

/*
  Pattern 3: Alternate Pairs Lighting
  - LEDs light up in pairs, alternating sequentially.
*/
void lightPattern3() {
  for (int i = 0; i < numberOfRelays; i += 2) {
    if (i + 1 < numberOfRelays) {
      digitalWrite(relayPins[i], LOW);      
      digitalWrite(relayPins[i + 1], LOW);  
      delay(timeDelay);
      digitalWrite(relayPins[i], HIGH);     
      digitalWrite(relayPins[i + 1], HIGH); 
    }
  }
}

/*
  Pattern 4: Random LED Lighting
  - LEDs turn ON in a random order.
*/
void lightPattern4() {
  for (int i = 0; i < numberOfRelays; i++) {
    int randRelay = random(0, numberOfRelays);
    digitalWrite(relayPins[randRelay], LOW);  
    delay(timeDelay);
    digitalWrite(relayPins[randRelay], HIGH); 
  }
}
