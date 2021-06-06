/*
* Program that accepts user input to change servo position.
* Accepts degrees from 30 to 150. Outputs servo location and destination
* 
* Uses SoftwareServo library in contrast to default servo library
* Code base pulled from SoftwareServo example
* SoftwareServo Link: https://playground.arduino.cc/ComponentLib/Servo/
* ***Not designed for ATtiny85 chip***
* 
*/

#include <SoftwareServo.h>

SoftwareServo myservo;  // create servo object to control a servo

int limits[2] = {30,150};  // set limitations (min/max: 0->180)
boolean refresh = false;  // toggle refresh on/off
int degree = 0;
int speed = 1; //controls how quickly the servo moves


void setup() 
{ 
  Serial.begin(9600);

  // attaches the servo on pin to the servo object (pin 13)
  myservo.attach(13);  

  // init angle of servo inbetween two limitations
  int center = ((limits[0]/2) + (limits[1]/2));
  myservo.write(center);
  degree = center;
}

void loop() {

  // refresh angle
    int angle = myservo.read();
    int direction = 0;

  //Gets and sets recieved serial data input
  if(Serial.available() > 0) {
    String degreeInput = "";
    
    while(Serial.available() > 0) { //While there is serial data to be read
      degreeInput += char(Serial.read()); //Concatenates the data read
      delay(2); //Necessary to read all of the characters fast enough
    }
    
    degree = degreeInput.toInt();
  }

  Serial.print("Destination: ");
  Serial.println(degree);
  Serial.print("Location: ");
  Serial.println(angle);

  if(degree >= limits[0] && degree <= limits[1]) {
      if (angle >= degree) {
        direction = -speed;
      }
      else if (angle <= degree) {
        direction = speed;
      }
  }
  else {
    Serial.println("Degree input OUT_OF_BOUNDS");
  }

  myservo.write(angle + direction);

  // set refresh one time / 2
  refresh = refresh ? false : true;
  if (refresh) SoftwareServo::refresh();
}
