/*
* Program that sends servo back and forth from 150 to 30 degrees.
* Utilizes pin 13 as data output. Outputs position to Serial Monitor.
* 
* Code pulled from example code on: https://playground.arduino.cc/ComponentLib/Servo/
* ***Not designed for ATtiny85 chip***
* 
*/

#include <SoftwareServo.h>

SoftwareServo myservo;  // create servo object to control a servo 

int speed = 1;
int limits[2] = {30,150};  // set limitations (min/max: 0->180)
boolean refresh = false;  // toggle refresh on/off

void setup() 
{ 
  Serial.begin(9600);

  // attaches the servo on pin to the servo object (pin 13)
  myservo.attach(13);  

  // init angle of servo inbetween two limitations
  myservo.write((limits[1]-limits[0])/2); 
} 

void loop() 
{ 
  // refresh angle
  int angle = myservo.read();

  // change direction when limits
  if (angle >= limits[1] || angle <= limits[0])  speed = -speed;

  myservo.write(angle + speed); 

  // set refresh one time / 2
  refresh = refresh ? false : true;
  if (refresh) SoftwareServo::refresh();

  Serial.print("Angle: ");
  Serial.println(angle);
} 
