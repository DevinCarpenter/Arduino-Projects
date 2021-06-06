/**
* This project is used to read NFC tags, but not RFID cards.
* Project saves and prints contents of tag.
* Also plays a tone every time a tag is scanned
*
* Resources are:
* https://github.com/adafruit/Adafruit-PN532 - original library for using PN532, not used in this project
* https://github.com/Seeed-Studio/PN532 - required library
* https://github.com/don/NDEF - Main library used, very high level in comparison to Adafruit-PN532
* 
**/

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include "pitches.h" //Gotten from https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody


PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

int notes[] = {
  NOTE_A4, NOTE_B4, NOTE_C3, NOTE_D4
};

void setup(void) {
    Serial.begin(9600);
    Serial.println("NDEF Reader");
    nfc.begin();
}

void loop(void) {
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        tag.print();

        //Accept tag tone sequence
        tone(8, notes[3], 200); //Pin, frequency, duration
        delay(200);
        tone(8, notes[1], 200); //Pin, frequency, duration


        //Deny tag tone sequence
        // tone(8, notes[0], 200); //Pin, frequency, duration
        // delay(200);
        // tone(8, notes[2], 200); //Pin, frequency, duration
    }
    delay(1000);
}