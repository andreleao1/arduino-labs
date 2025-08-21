/**
 * Project: SOS in Morse Code with Arduino
 *
 * Goal:
 * - When the button is pressed, the Arduino should emit the SOS sequence 
 *   on an LED, following the timing rules of Morse code.
 *
 * Introduction:
 * - Morse code is formed by dots (·) and dashes (–).
 *   -> S = ... (three dots)
 *   -> O = --- (three dashes)
 *
 * Timing rules (with one unit = 200 ms):
 * - Dot (·): LED ON for 1 unit
 * - Dash (–): LED ON for 3 units
 * - Space between signals within the same letter: LED OFF for 1 unit
 * - Space between letters: LED OFF for 3 units
 * - Space between words: LED OFF for 7 units
 *
 * Code structure:
 * - Functions were created to represent dot, dash, and the different pause types.
 * - In the main loop, when the button is pressed, the Arduino executes the 
 *   sequence corresponding to the word SOS by calling the functions in the correct order.
 */

int buttonState = 0;

const int buttonPin = 6;
const int ledPin = 7;
const int oneUnitTime = 200;
const int threeUnitTime = oneUnitTime * 3;
const int sevenUnitTime = oneUnitTime * 7;

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(oneUnitTime);
  digitalWrite(ledPin, LOW);
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(threeUnitTime);
  digitalWrite(ledPin, LOW);
}

void spaceWithinLetter() {
  delay(oneUnitTime);
}

void spaceBetweenLetters() {
  delay(threeUnitTime);
}

void spaceBetweenWords() {
  delay(sevenUnitTime);
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH) {
    // S = ...
    dot();
    spaceWithinLetter();
    dot();
    spaceWithinLetter();
    dot();
    spaceBetweenLetters();

    // O = ---
    dash();
    spaceWithinLetter();
    dash();
    spaceWithinLetter();
    dash();
    spaceBetweenLetters();
    
    // S = ...
    dot();
    spaceWithinLetter();
    dot();
    spaceWithinLetter();
    dot();
    spaceBetweenWords();
  }
}
