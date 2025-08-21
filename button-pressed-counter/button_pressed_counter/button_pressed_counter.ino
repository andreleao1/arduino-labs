const int buttonPin = 6;
int n = 0;
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH) {
    n++;
    Serial.print("The button was pressed ");
    Serial.print(n);
    Serial.println(" times");
    delay(500);
  }

}
