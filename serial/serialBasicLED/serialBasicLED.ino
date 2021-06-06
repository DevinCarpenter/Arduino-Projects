/*
*  Very first serial program
*  Used this video for reference: https://www.youtube.com/watch?v=KYWCkdrCUKg
*
*  This program utilizes serial code to change output of pin 13 from HIGH to LOW.
*  Pin 13 is connected to an LED, and so is controlled via the Serial Monito in
*  the Arduino IDE by typing '1' or '0' for On and Off respectively.
*/

void setup() {
  pinMode(13,OUTPUT); //Define pin 13 as output
  digitalWrite(13,LOW); //Set pin 13 output to low

  Serial.begin(9600); //Start serial RX/TX at a 9600 bps Baud rate (bits per second)

}

void loop() {
  if(Serial.available() > 0) { //If there is serial data to be read
    char letter = Serial.read(); //Sets letter to be the variable that changes on serial input

    // Sends value to pin 13
    if(letter == '1') {
      digitalWrite(13,HIGH); //Sets 13 to HIGH; Flashes RX (Recieves user data) on arduino 
      Serial.println("ON");  //Sets 13 to LOW; Flashes TX (Sends data to serial monitor)
    }
    else if(letter == '0') {
      digitalWrite(13,LOW);
      Serial.println("OFF");
    }
    
    // Reads value from pin 13
    if(digitalRead(13)) { //Reads pin 13 value. Useful in example for debugging
      Serial.println("LED IS ON");
    }
    else {
      Serial.println("LED IS OFF");
    }
  }

//  //Reads the serial data as a string and prints it
//  if(Serial.available() > 0) {
//    String msg = "";
//    
//    while(Serial.available() > 0) { //While there is serial data to be read
//      msg += char(Serial.read()); //Concatenates the data read
//      delay(2); //Necessary to read all of the characters fast enough
//    }
//
//    Serial.println(msg);
//  }
}
