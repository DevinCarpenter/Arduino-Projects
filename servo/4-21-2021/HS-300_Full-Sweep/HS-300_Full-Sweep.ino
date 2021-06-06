#include <ATTinyCore.h>
#include <Servo_ATTinyCore.h>


//#include <Servo.h>


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.attach(1);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  /*
    - The servo in particular (HS-300) uses this code to go from 0 to 90 to 180
    
    - It seems that the servo can go outside the '5' and '157' value but it is
      pushing it's limits and at times causes a grinding as if its trying to go
      past its mechanical stopper.
  */
  
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


////This code (untested with working code) is used to move the servo 1 degree at a time
//  for (pos = 0; pos <= 160; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(30);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 160; pos >= 20; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(30);                       // waits 15ms for the servo to reach the position
//  }
}
