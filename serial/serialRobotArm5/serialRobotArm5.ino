#include <Servo.h>

/*
 *
 * This program controls 4 servos of a robot arm with 2 joysticks.
 * The servos will snap back to center when you let go of joysticks.
 * Pressing the right joystick down (J1) will toggle between speed modes
 * 
 * **Important** You cannot power these with arduino.
 * Connect ground of external power supply to ground of arduino and servos/joysticks
 * Connect +5V of external power supply to Vcc of servos & joystick but NOT TO ARDUINO
 * DO NOT CONNECT EXTERNAL POWER SUPPLY POSITIVE TO +5 ON ARDUINO
 * Reference wiring video: https://www.youtube.com/watch?v=iBUU-lx-wPM
 * Inspiration for robot arm design: https://www.youtube.com/watch?v=ADJGxOrEZAM
 * 
 *
 */

//#include <SoftwareServo.h>

//SoftwareServo S1_;  // create servo object to control a servo
//SoftwareServo S2_;  // create servo object to control a servo
//SoftwareServo S3_;  // create servo object to control a servo
//SoftwareServo S4_;  // create servo object to control a servo

#include <Servo.h>

Servo S1_;  // create servo object to control a servo
Servo S2_;  // create servo object to control a servo
Servo S3_;  // create servo object to control a servo
Servo S4_;  // create servo object to control a servo

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
boolean J1_SW_pressed = false;
//int J1_SW_state_read = 0;
//boolean buttonPressed
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
int S1_Limits[2] = {0,180};  // set limitations (min/max: 0->180)
int S2_Limits[2] = {0,180};  // set limitations (min/max: 0->180)
int S3_Limits[2] = {0,180};  // set limitations (min/max: 0->180)
int S4_Limits[2] = {45,110};  // set limitations (min/max: 0->180)
boolean refresh = false;  // toggle refresh on/off
int S1_Degree = 0;
int S2_Degree = 0;
int S3_Degree = 0;
int S4_Degree = 0;
int S1_Speed = 0;
int S2_Speed = 0;
int S3_Speed = 0;
int S4_Speed = 0;
int S1_Speed_Limit = 2; //controls how quickly the servo can move
int S2_Speed_Limit = 2; //controls how quickly the servo can move
int S3_Speed_Limit = 2; //controls how quickly the servo can move
int S4_Speed_Limit = 1; //controls how quickly the servo can move
int S1_Map = 0;
int S2_Map = 0;
int S3_Map = 0;
int S4_Map = 0;
int speedModes[3] = {1,2,3}; //Define the speeds which can be toggled between
int speedMode = 2; //Set initial speed mode (speedModes[1] if this value is 1) 


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

  //Set servo initial speed limit
  S1_Speed_Limit = speedModes[speedMode - 1];
  S2_Speed_Limit = speedModes[speedMode - 1];
  S3_Speed_Limit = speedModes[speedMode - 1];
  
}

void loop() {

  //Reset servo direction speeds
  S1_Speed = 0;
  S2_Speed = 0;
  S3_Speed = 0;
  S4_Speed = 0;

  //Read Joystick 1 inputs
  J1_xPosition = analogRead(J1_VRx);
  J1_yPosition = analogRead(J1_VRy);
  J1_SW_state = digitalRead(J1_SW);
  J1_mapX = map(J1_xPosition, 0, 1023, -1024, 1024); //X-position of joystick
  J1_mapY = map(J1_yPosition, 0, 1023, -1024, 1024); //Y-position of joystick

  J2_xPosition = analogRead(J2_VRx);
  J2_yPosition = analogRead(J2_VRy);
  J2_SW_state = digitalRead(J2_SW);
  J2_mapX = map(J2_xPosition, 0, 1023, -1024, 1024); //X-position of joystick
  J2_mapY = map(J2_yPosition, 0, 1023, -1024, 1024); //Y-position of joystick


  //Fix offsets for joysticks (custom fixes because these joysticks aren't perfect :/)
  J1_mapX += 6;
  J1_mapY += 20;
  J2_mapX -= 2;
  J2_mapY += 12;

  delay(10);

  boolean J1_SW_toggled = false;
  //If the button is down
  if(J1_SW_state == 0) {
    J1_SW_pressed = true;
    Serial.println("Pressed");
  }
  //If the button was down and is now up
  if(J1_SW_pressed == true && J1_SW_state == 1) {
    J1_SW_pressed = false;
    J1_SW_toggled = true;
    Serial.println("Unpressed");
  }

  //Cycle the speed mode for servos 1, 2 and 3
  if(J1_SW_toggled) {
    Serial.println("Toggled");
    J1_SW_toggled = false;
    if (speedMode != speedModes[(sizeof(speedModes) / sizeof(int)) - 1]) { //This is how to get length of speedModes array of byte type int
      speedMode += 1;
    }
    else {
      speedMode = 1;
    }
    Serial.println(speedMode);

    S1_Speed_Limit = speedModes[speedMode - 1];
    S2_Speed_Limit = speedModes[speedMode - 1];
    S3_Speed_Limit = speedModes[speedMode - 1];
  }

  int stutterSetting = 100; //+- buffer to keep servos from moving due to imperfect readouts from joysticks
  
  if(J1_mapY > stutterSetting || J1_mapY < -stutterSetting) {
    S1_Speed = map(J1_mapY, -512, 512, S1_Speed_Limit, -S1_Speed_Limit);
  }
  if(J1_mapX > stutterSetting || J1_mapX < -stutterSetting) {
    S2_Speed = map(J1_mapX, -512, 512, S2_Speed_Limit, -S2_Speed_Limit);
  }
  if(J2_mapX > stutterSetting || J2_mapX < -stutterSetting) {
    S3_Speed = map(J2_mapX, -512, 512, S3_Speed_Limit, -S3_Speed_Limit);
  }
  if(J2_mapY > stutterSetting || J2_mapY < -stutterSetting) {
    S4_Speed = map(J2_mapY, -512, 512, -S4_Speed_Limit, S4_Speed_Limit);
  }


  if(S1_Speed != 0) {
    if((S1_Degree + S1_Speed) < S1_Limits[1] && (S1_Degree + S1_Speed) > S1_Limits[0]) {
      S1_Degree += S1_Speed;
      S1_.write(S1_Degree);
      delay(10);
    }
  }

  if(S2_Speed != 0) {
    if((S2_Degree + S2_Speed) < S2_Limits[1] && (S2_Degree + S2_Speed) > S2_Limits[0]) {
      S2_Degree += S2_Speed;
      S2_.write(S2_Degree);
      delay(10);
    }
  }

  if(S3_Speed != 0) {
    if((S3_Degree + S3_Speed) < S3_Limits[1] && (S3_Degree + S3_Speed) > S3_Limits[0]) {
      S3_Degree += S3_Speed;
      S3_.write(S3_Degree);
      delay(10);
    }
  }

  if(S4_Speed != 0) {
    if((S4_Degree + S4_Speed) < S4_Limits[1] && (S4_Degree + S4_Speed) > S4_Limits[0]) {
      S4_Degree += S4_Speed;
      S4_.write(S4_Degree);
      delay(10);
    }
  }

//  Serial.print("J2_X: ");
//  Serial.print(J2_mapX);
//  Serial.print(" | J2_Y: ");
//  Serial.print(J2_mapY);
//  Serial.print(" | J1_Button: ");
//  Serial.print(J2_SW_state);
//  Serial.print(" | S3_Speed: ");
//  Serial.print(S4_Speed);
//  Serial.print(" | S3_Degree: ");
//  Serial.println(S4_Degree);

//  refresh = refresh ? false : true; // set refresh one time / 2
//  if (refresh) SoftwareServo::refresh();
}
