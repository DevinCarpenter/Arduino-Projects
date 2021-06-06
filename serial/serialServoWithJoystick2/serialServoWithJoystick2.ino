/*
 *
 * This program lets you control multiple servos with a joystick
 * **Important** You cannot power these with arduino.
 * Connect ground of external power supply to ground of arduino and servos/joystick
 * Connect +5V of external power supply to Vcc of servos & joystick but NOT TO ARDUINO
 * DO NOT CONNECT EXTERNAL POWER SUPPLY POSITIVE TO +5 ON ARDUINO
 * Reference wiring video: https://www.youtube.com/watch?v=iBUU-lx-wPM
 * 
 * Code is a mashup of serialServo1 and serialJoystick1
 *
 */

#include <SoftwareServo.h>

SoftwareServo servo1;  // create servo object to control a servo
SoftwareServo servo2;  // create servo object to control a servo

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
int Servo1Output = 13;
int Servo2Output = 12;


//Servo Variables
int servo1Limits[2] = {30,150};  // set limitations (min/max: 0->180)
int servo2Limits[2] = {30,150};  // set limitations (min/max: 0->180)
boolean refresh = false;  // toggle refresh on/off
int servo1Degree = 0;
int servo2Degree = 0;
int servo1Speed = 2; //controls how quickly the servo moves
int servo2Speed = 2; //controls how quickly the servo moves
int servo1Map = 0;
int servo2Map = 0;


void setup() {
  Serial.begin(9600); 

  //Assign Joystick pins
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);

  //Assign Servo pin
  servo1.attach(Servo1Output);
  servo2.attach(Servo2Output);

  //Get center of Servo limitations
  int servo1Center = ((servo1Limits[0]/2) + (servo1Limits[1]/2));
  int servo2Center = ((servo2Limits[0]/2) + (servo2Limits[1]/2));

  //Send servos to center
  servo1.write(servo1Center);
  servo2.write(servo2Center);

  //Set servo current degrees as at center
  servo1Degree = servo1Center;
  servo2Degree = servo1Center;
  
}

void loop() {

  //Read Joystick inputs
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512); //X-position of joystick
  mapY = map(yPosition, 0, 1023, -512, 512); //Y-position of joystick
  delay(10);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);
  

  //Write Servo positions
  servo1Map = map(mapX, -512, 512, servo1Limits[0], servo1Limits[1]);
  servo2Map = map(mapY, -512, 512, servo2Limits[0], servo2Limits[1]);
  
  servo1.write(servo1Map);
  servo2.write(servo2Map);

  refresh = refresh ? false : true; // set refresh one time / 2
  if (refresh) SoftwareServo::refresh();

  Serial.print("Servo1Map: ");
  Serial.print(servo1Map);
  Serial.print("Servo2Map: ");
  Serial.print(servo2Map);

}
