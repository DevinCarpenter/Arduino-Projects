/*
 Controlling Servo with ATtiny85
 Helpful reference for understanding pins to program to: https://www.instructables.com/How-to-Program-an-Attiny85-From-an-Arduino-Uno/

 Helpful reference understanding servo Milliseconds to Degrees conversion: http://www.seattlerobotics.org/guide/servos.html
 1.5 ms Neutral (Middle)
 1.25 ms 0 Degrees
 1.75 ms 180 Degrees
*/

void setup() {
  pinMode(PB1, OUTPUT); // *** Refer to reference above to find which pin PB1 is on the ATtiny85 (Pin 6 on the chip) ***
}

void loop() {

 for(int i = 0; i<20; ++i) {
    digitalWrite(PB1, HIGH);
    delayMicroseconds(1250); //45 degree angle
    digitalWrite(PB1, LOW);
    delay(19);
 }
 delay(2000);
 for(int i = 0; i<20; ++i) {
    digitalWrite(PB1, HIGH);
    delayMicroseconds(1500); //Neutral
    digitalWrite(PB1, LOW);
    delay(19);
 }
 delay(2000);
 for(int i = 0; i<20; ++i) {
    digitalWrite(PB1, HIGH);
    delayMicroseconds(1750); //45 degree angle
    digitalWrite(PB1, LOW);
    delay(19);
 }
 delay(2000);

}
