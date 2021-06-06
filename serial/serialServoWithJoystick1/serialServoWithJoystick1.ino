/*
 * This program lets you control a servo with a joystick using
 * serial data. Open serial monitor to view details.
 * 
 * Code is a mashup of serialServo1 and serialJoystick1
 *
 */

#include <SoftwareServo.h>

SoftwareServo myservo;  // create servo object to control a servo

//Joystick inputs (Joystick -> Arduino)
int VRx = A0;
int VRy = A1;
int SW = 2;

//Joystick variables
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

//Servo output (Arduino -> Servo)
int P13 = 13;

//Servo Variables
int limits[2] = {30,150};  // set limitations (min/max: 0->180)
boolean refresh = false;  // toggle refresh on/off
int degree = 0;
int speed = 2; //controls how quickly the servo moves
int servoMap1 = 0;


void setup() {
  Serial.begin(9600); 

  //Assign Joystick pins
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);

  //Assign Servo pin
  myservo.attach(P13);

  //Get and set center of Servo limitations
  int center = ((limits[0]/2) + (limits[1]/2));
  myservo.write(center);
  degree = center;
  
}

void loop() {

  //Read Joystick inputs
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512); //X-position of joystick
  mapY = map(yPosition, 0, 1023, -512, 512); //Y-position of joystick
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);
  

  //Write Servo positions
  servoMap1 = map(mapX, -512, 512, limits[0], limits[1]);
  
  myservo.write(servoMap1);

  refresh = refresh ? false : true; // set refresh one time / 2
  if (refresh) SoftwareServo::refresh();

  Serial.print("ServoMap: ");
  Serial.print(servoMap1);

}
