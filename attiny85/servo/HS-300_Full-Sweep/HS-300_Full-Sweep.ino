#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // Make servo go to 0 degrees 
   myservo.write(5); 
   delay(1000); 
   // Make servo go to 90 degrees 
   myservo.write(90); 
   delay(1000); 
   // Make servo go to 180 degrees 
   myservo.write(157); 
   delay(1000);
   // Make servo go to 90 degrees 
   myservo.write(90); 
   delay(1000); 

}
