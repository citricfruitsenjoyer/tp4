void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(7, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(40000);                      // wait for a second
  digitalWrite(7, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second

  digitalWrite(8, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(60000);                      // wait for a second
  digitalWrite(8, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
