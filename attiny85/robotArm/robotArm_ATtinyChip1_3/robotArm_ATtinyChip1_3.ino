/*
 *
 * This program controls 4 servos of a robot arm with 2 joysticks.
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

#include <Arduino.h> // required for main()

/*
 * You can specify TX_PIN here, but then you must remove ATtinySerialOut.cpp from the library,
 * otherwise you will see "multiple definition of" errors.
 */
#if defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#define TX_PIN PA1 // (package pin 2 / TXD on Tiny167) - can use one of PA0 to PA7 here
#else
#define TX_PIN PB2 // (package pin 7 on Tiny85) - can use one of PB0 to PB4 (+PB5) here
#endif
#include "ATtinySerialOut.cpp.h" // activate this to enable TX_PIN settings

#include "ATtinySerialOut.h"

//#include <SoftwareSerial.h>
//
//#define RX    3   // *** D3, Pin 2
//#define TX    4   // *** D4, Pin 3
//
////SoftwareSerial myserial(RX, TX); //Make sure not to use 'Serial' as that is in use in a conflicting namespace
//SoftwareSerial myserial(RX, TX); //Make sure not to use 'Serial' as that is in use in a conflicting namespace

#include <Servo_ATTinyCore.h>

Servo S1_;  // create servo object to control a servo
Servo S2_;  // create servo object to control a servo

//Joystick 1 inputs (Joystick -> Arduino)
int J1_VRx = PIN_PB3; //Attiny85 PB3 (Physical pin 2) - as per SpenceKonde ATtinyCore Github 'You cannot use the Pxn notation (ie, PB2, PA1, etc) to refer to pins ... use PIN_Pxn (ex, PIN_PB2)'
int J1_VRy = PIN_PB2; // Attiny85 PB4 (Physical pin 7)
//int J1_SW = PIN_PB4; // Attiny85 PB2 (Physical pin 3)

//Joystick 1 variables
int J1_xPosition = 0;
int J1_yPosition = 0;
int J1_SW_state = 0;
boolean J1_SW_pressed = false;
int J1_mapX = 0;
int J1_mapY = 0;

//Servo output (Arduino -> Servo)
int S1_Output = PIN_PB1;
int S2_Output = PIN_PB4;

//Servo Variables
int S1_Limits[2] = {0,180};  // set limitations (min/max: 0->180)
int S2_Limits[2] = {0,180};  // set limitations (min/max: 0->180)
boolean refresh = false;  // toggle refresh on/off
int S1_Degree = 0;
int S2_Degree = 0;
int S1_Speed = 0;
int S2_Speed = 0;
int S1_Speed_Limit = 2; //controls how quickly the servo can move
int S2_Speed_Limit = 2; //controls how quickly the servo can move
int speedModes[3] = {1,2,3}; //Define the speeds which can be toggled between
int speedMode = 2; //Set initial speed mode (speedModes[1] if this value is 1) 


void setup() {

  initTXPin();

  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_ATTINY_SERIAL_OUT));

  writeString("OSCCAL=");
  writeUnsignedByteHexWithPrefix(OSCCAL);
    
  myserial.begin(9600); 

  //Assign Joystick 1 pins
  pinMode(J1_VRx, INPUT);
  pinMode(J1_VRy, INPUT);
  //pinMode(J1_SW, INPUT_PULLUP);

  //Assign Servo pin
  S1_.attach(S1_Output);
  S2_.attach(S2_Output);

  //Get center of Servo limitations
  int S1_Center = ((S1_Limits[0]/2) + (S1_Limits[1]/2));
  int S2_Center = ((S2_Limits[0]/2) + (S2_Limits[1]/2));

  //Send servos to center
  S1_.write(S1_Center);
  S2_.write(S2_Center);

  //Set servo current degrees as at center
  S1_Degree = S1_Center;
  S2_Degree = S2_Center;

  //Set servo initial speed limit
  S1_Speed_Limit = speedModes[speedMode - 1];
  S2_Speed_Limit = speedModes[speedMode - 1];
  
}

void loop() {

  //Reset servo direction speeds
  S1_Speed = 0;
  S2_Speed = 0;

  //Read Joystick 1 inputs
  J1_xPosition = analogRead(J1_VRx);
  J1_yPosition = analogRead(J1_VRy);
  //J1_SW_state = digitalRead(J1_SW);
  J1_mapX = map(J1_xPosition, 0, 1023, -1024, 1024); //X-position of joystick
  J1_mapY = map(J1_yPosition, 0, 1023, -1024, 1024); //Y-position of joystick

  //Fix offsets for joysticks (custom fixes because these joysticks aren't perfect :/)
  J1_mapX += 6;
  J1_mapY += 20;

  delay(10);

//  boolean J1_SW_toggled = false;
//  //If the button is down
//  if(J1_SW_state == 0) {
//    J1_SW_pressed = true;
//    //Joystick button pressed
//  }
//  //If the button was down and is now up
//  if(J1_SW_pressed == true && J1_SW_state == 1) {
//    J1_SW_pressed = false;
//    J1_SW_toggled = true;
//    //Joystick button released
//  }
//
//  //Cycle the speed mode for servos 1, 2 and 3
//  if(J1_SW_toggled) {
//    J1_SW_toggled = false;
//    if (speedMode != speedModes[(sizeof(speedModes) / sizeof(int)) - 1]) { //This is how to get length of speedModes array of byte type int
//      speedMode += 1;
//    }
//    else {
//      speedMode = 1;
//    }
//    S1_Speed_Limit = speedModes[speedMode - 1];
//    S2_Speed_Limit = speedModes[speedMode - 1];
//  }

  int stutterSetting = 100; //+- buffer to keep servos from moving due to imperfect readouts from joysticks
  
  if(J1_mapY > stutterSetting || J1_mapY < -stutterSetting) {
    S1_Speed = map(J1_mapY, -512, 512, S1_Speed_Limit, -S1_Speed_Limit);
  }
  if(J1_mapX > stutterSetting || J1_mapX < -stutterSetting) {
    S2_Speed = map(J1_mapX, -512, 512, S2_Speed_Limit, -S2_Speed_Limit);
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

//  myserial.print("J1_X: ");
//  myserial.print(J1_mapX);
//  myserial.print(" | J1_Y: ");
//  myserial.print(J1_mapY);
//  myserial.print(" | S1_Speed: ");
//  myserial.print(S1_Speed);
//  myserial.print(" | S1_Degree: ");
//  myserial.print(S1_Degree);
//  myserial.print(" | S2_Speed: ");
//  myserial.print(S2_Speed);
//  myserial.print(" | S2_Degree: ");
//  myserial.println(S2_Degree);
}
