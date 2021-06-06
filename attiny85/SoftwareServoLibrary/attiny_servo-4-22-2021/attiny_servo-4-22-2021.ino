
/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

 If Servo library is installed to libraries, then that version (which doesn't support ATtiny parts)
 will be used instead of the one included with the core, which does. To get around this,
 include  Servo_ATTinyCore.h instead - this will always use the version that came with core.

 Library downloaded at: https://playground.arduino.cc/ComponentLib/Servo/
 Video reference at: https://www.youtube.com/watch?v=8KIR4aokrsU
*/

#include <SoftwareServo.h>

SoftwareServo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(PB1);  // attaches the servo on pin 9 to the servo object
  //myservo.attach(PB1, 1250, 1500  ); // - Attaches to a pin setting min and max values in microseconds (default min is 544, max is 2400)
}

void loop() {
  for(int i = 0; i<20; ++i) {
    myservo.write(45);
    delay(19);
    SoftwareServo::refresh();
 }
 delay(2000);
 for(int i = 0; i<20; ++i) {
    myservo.write(90);
    delay(19);
    SoftwareServo::refresh();
 }
 delay(2000);
   
}
