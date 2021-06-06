/*
  From Blink Example
  ATtiny85 chip programmed to blink from reference: https://www.youtube.com/watch?v=Z_MhVSlMZI8
  My very first chip programmed! Ever!


  Helpful reference for understanding pins to program to: https://www.instructables.com/How-to-Program-an-Attiny85-From-an-Arduino-Uno/
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(3, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
}
