/*
 *
 * This program controls 4 servos of a robot arm with 2 joysticks.
 * The servos will snap back to center when you let go of joysticks.
 * You can set each servo's speed using variables below.
 * 
 * **Important** You cannot power these with arduino.
 * Connect ground of external power supply to ground of arduino and servos/joysticks
 * Connect +5V of external power supply to Vcc of servos & joystick but NOT TO ARDUINO
 * DO NOT CONNECT EXTERNAL POWER SUPPLY POSITIVE TO +5 ON ARDUINO
 * Reference wiring video: https://www.youtube.com/watch?v=iBUU-lx-wPM
 * Inspiration for robot arm design: https://www.youtube.com/watch?v=ADJGxOrEZAM
 * 
 * Code based off project 'serialServoWithJoystick2'
 *
 */

#include <SoftwareServo.h>

SoftwareServo S1_;  // create servo object to control a servo
SoftwareServo S2_;  // create servo object to control a servo
SoftwareServo S3_;  // create servo object to control a servo
SoftwareServo S4_;  // create servo object to control a servo

//Joystick 1 inputs (Joystick -> Arduino)
int J1_VRx = A0;
int J1_VRy = A1;
int J1_SW = 2;

//Joystick 2 inputs

int J2_VRx = A2;
int J2_VRy = A3;
int J2_SW = 3;

//Joystick 1 variables
int J1_xPosition = 0;
int J1_yPosition = 0;
int J1_SW_state = 0;
int J1_mapX = 0;
int J1_mapY = 0;

//Joystick 2 variables
int J2_xPosition = 0;
int J2_yPosition = 0;
int J2_SW_state = 0;
int J2_mapX = 0;
int J2_mapY = 0;

//Servo output (Arduino -> Servo)
int S1_Output = 13;
int S2_Output = 12;
int S3_Output = 11;
int S4_Output = 10;


//Servo Variables
int S1_Limits[2] = {30,150};  // set limitations (min/max: 0->180)
int S2_Limits[2] = {30,150};  // set limitations (min/max: 0->180)
int S3_Limits[2] = {30,150};  // set limitations (min/max: 0->180)
int S4_Limits[2] = {30,150};  // set limitations (min/max: 0->180)
boolean refresh = false;  // toggle refresh on/off
int S1_Degree = 0;
int S2_Degree = 0;
int S3_Degree = 0;
int S4_Degree = 0;
int S1_Speed = 4; //controls how quickly the servo moves
int S2_Speed = 4; //controls how quickly the servo moves
int S3_Speed = 4; //controls how quickly the servo moves
int S4_Speed = 4; //controls how quickly the servo moves
int S1_Map = 0;
int S2_Map = 0;
int S3_Map = 0;
int S4_Map = 0;


void setup() {
  Serial.begin(9600); 

  //Assign Joystick 1 pins
  pinMode(J1_VRx, INPUT);
  pinMode(J1_VRy, INPUT);
  pinMode(J1_SW, INPUT_PULLUP);

  //Assign Joystick 2 pins
  pinMode(J2_VRx, INPUT);
  pinMode(J2_VRy, INPUT);
  pinMode(J2_SW, INPUT_PULLUP);

  //Assign Servo pin
  S1_.attach(S1_Output);
  S2_.attach(S2_Output);
  S3_.attach(S3_Output);
  S4_.attach(S4_Output);

  //Get center of Servo limitations
  int S1_Center = ((S1_Limits[0]/2) + (S1_Limits[1]/2));
  int S2_Center = ((S2_Limits[0]/2) + (S2_Limits[1]/2));
  int S3_Center = ((S3_Limits[0]/2) + (S3_Limits[1]/2));
  int S4_Center = ((S4_Limits[0]/2) + (S4_Limits[1]/2));

  //Send servos to center
  S1_.write(S1_Center);
  S2_.write(S2_Center);
  S3_.write(S3_Center);
  S4_.write(S4_Center);

  //Set servo current degrees as at center
  S1_Degree = S1_Center;
  S2_Degree = S2_Center;
  S3_Degree = S3_Center;
  S4_Degree = S4_Center;
  
}

void loop() {

  //Read Joystick 1 inputs
  J1_xPosition = analogRead(J1_VRx);
  J1_yPosition = analogRead(J1_VRy);
  J1_SW_state = digitalRead(J1_SW);
  J1_mapX = map(J1_xPosition, 0, 1023, -512, 512); //X-position of joystick
  J1_mapY = map(J1_yPosition, 0, 1023, -512, 512); //Y-position of joystick

  J2_xPosition = analogRead(J2_VRx);
  J2_yPosition = analogRead(J2_VRy);
  J2_SW_state = digitalRead(J2_SW);
  J2_mapX = map(J2_xPosition, 0, 1023, -512, 512); //X-position of joystick
  J2_mapY = map(J2_yPosition, 0, 1023, -512, 512); //Y-position of joystick
  delay(10);
  

  //Map Servo positions
  S1_Map = map(J1_mapX, -512, 512, S1_Limits[0], S1_Limits[1]);
  S2_Map = map(J1_mapY, -512, 512, S2_Limits[0], S2_Limits[1]);
  S3_Map = map(J2_mapX, -512, 512, S2_Limits[0], S2_Limits[1]);
  S4_Map = map(J2_mapY, -512, 512, S2_Limits[0], S2_Limits[1]);

  Serial.print("J1_X: ");
  Serial.print(J1_mapX);
  Serial.print(" | J1_Y: ");
  Serial.print(J1_mapY);
  Serial.print(" | J1_Button: ");
  Serial.print(J1_SW_state);
  Serial.print(" | S1_Map: ");
  Serial.print(S1_Map);
  Serial.print(" | S1_Degree: ");
  Serial.println(S1_Degree);

  //Joystick_1 X  
  if (S1_Degree > S1_Map && (S1_Degree - S1_Map) > 5) {
    S1_Degree -= S1_Speed;
    S1_.write(S1_Degree);
  }
  else if (S1_Degree < S1_Map && (S1_Degree - S1_Map) < -5) {
    S1_Degree += S1_Speed;
    S1_.write(S1_Degree);
  }
  //Joystick_1 Y
  if (S2_Degree > S2_Map && (S2_Degree - S2_Map) > 5) {
    S2_Degree -= S2_Speed;
    S2_.write(S2_Degree);
    
  }
  else if (S2_Degree < S2_Map && (S2_Degree - S2_Map) < -5) {
    S2_Degree += S2_Speed;
    S2_.write(S2_Degree);
    
  }
  //Joystick_2 X
  if (S3_Degree > S3_Map && (S3_Degree - S3_Map) > 5) {
    S3_Degree -= S3_Speed;
    S3_.write(S3_Degree);
    
  }
  else if (S3_Degree < S3_Map && (S3_Degree - S3_Map) < -5) {
    S3_Degree += S3_Speed;
    S3_.write(S3_Degree);
    
  }
  //Joystick_2 Y
  if (S4_Degree > S4_Map && (S4_Degree - S4_Map) > 5) {
    S4_Degree -= S4_Speed;
    S4_.write(S4_Degree);
    
  }
  else if (S4_Degree < S4_Map && (S4_Degree - S4_Map) < -5) {
    S4_Degree += S4_Speed;
    S4_.write(S4_Degree);
    
  }

  refresh = refresh ? false : true; // set refresh one time / 2
  if (refresh) SoftwareServo::refresh();

//  Serial.print("S1_Map: ");
//  Serial.print(S1_Map);
//  Serial.print("S2_Map: ");
//  Serial.print(S2_Map);

}
