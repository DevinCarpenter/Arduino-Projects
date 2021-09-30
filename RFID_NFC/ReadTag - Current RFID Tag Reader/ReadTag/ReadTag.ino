/**
*
* Author: Devin Carpenter
* 
* This project is used to read NFC tags (no RFID cards) and to send out the NFC
* data over Serial to a raspberry pi. The raspberry pi parses out the tag details
* it needs and writes them to a database. From there the raspberry pi sends back
* results via Serial - which the Arduino parses, and then sends out a tone over a
* speaker to indicate whether the tag data was added or not, and any errors that
* may have occurred.
* 
* This code was uploaded to an Arduino Uno with an Adafruit PN532 RFID/NFC shield attached.
* 
*
* Resources are:
* https://github.com/adafruit/Adafruit-PN532 - original library for using PN532, not used in this project
* https://github.com/Seeed-Studio/PN532 - required library
* https://github.com/don/NDEF - Main library used, very high level in comparison to Adafruit-PN532
* https://youtu.be/tCJgnBI1D5o - Video detailing basic string manipulation for C strings and communication over serial.
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
    NOTE_A4, NOTE_B4, NOTE_C3, NOTE_D4};

int notes_lessAnnoying[] = {
    NOTE_E2, NOTE_E2};

char rawData[100] = "";            //buffer where incoming serial data will be stored
char keyword[] = "1337PiMessage="; //keyword used to determine start of new message from pi

void tagAddedTone()
{
    //Added tag tone sequence
    tone(8, notes[3], 200); //Pin, frequency, duration
    delay(200);
    tone(8, notes[1], 200); //Pin, frequency, duration
}

void tagAlreadyExistsTone()
{
    //Deny tag tone sequence
    tone(8, notes[0], 200); //Pin, frequency, duration
    delay(200);
    tone(8, notes[2], 200); //Pin, frequency, duration
}

void tagErrorTone()
{
    //Error tag tone
    tone(8, notes[0], 200); //Pin, frequency, duration
    delay(200);
    tone(8, notes[2], 200); //Pin, frequency, duration
}

void handleResponse(char *piMessage)
{
    char message1[] = "Tag added to database";
    char message2[] = "Tag already in database";
    char message3[] = "Error adding tag to database";
    char message4[] = "Token too big";
    bool errorOccurred = false;
    char errorMessage[40];
    
    if (strcmp(piMessage, message1) == 0)
    {
        tagAddedTone();
    }
    else if (strcmp(piMessage, message2) == 0)
    {
        tagAlreadyExistsTone();
    }
    else if (strcmp(piMessage, message3) == 0)
    {
        tagErrorTone();
        delay(200);
        tagErrorTone();
        delay(200);
        errorOccurred = true;
    }
    else if (strcmp(piMessage, message4) == 0)
    {
        tagErrorTone();
        delay(200);
        tagErrorTone();
        delay(200);
        errorOccurred = true;
        strcpy(errorMessage, "TOKEN TOO BIG");
    }
    else
    { //Invalid message recieved - send error tone 3 times.
         tagErrorTone();
         delay(200);
         tagErrorTone();
         delay(200);
         tagErrorTone();
         errorOccurred = true;
         strcpy(errorMessage, "UNKNOWN MESSAGE RECIEVED");
    }
    // Say what was recieved back over serial:
    if(errorOccurred == true)
    {
        Serial.print("1337ArduinoMessage=Error:");
        Serial.print(errorMessage);
        Serial.print(",");
        Serial.print("Recieved:");
        Serial.println(piMessage);
    }
    else
    {
        Serial.print("1337ArduinoMessage=Recieved:");
        Serial.println(piMessage);
    }
    
}

void setup(void)
{
    Serial.begin(9600);
    Serial.println("NDEF Reader");
    nfc.begin();
}

void loop(void)
{
    //If a tag was scanned...
    if (nfc.tagPresent())
    {
        //tagAddedTone();
        NfcTag tag = nfc.read(); // Read the tag from the NFC Reader
        tag.print();             // Send the tag data over Serial (to Raspberry Pi)
        delay(1000);
    }

    if (Serial.available() > 0)
    { // new data in
        //Read the bytes of Serial data until we hit a newline character or we reach the
        // buffer limit which is its size (100) minus 1 so we still have room to
        // add an EOL character. The amount of bytes in the message is returned from the
        // readBytesUntil method.
        size_t byteCount = Serial.readBytesUntil('\n', rawData, sizeof(rawData) - 1); //read in data to buffer
        rawData[byteCount] = NULL;                                                    //put an end character on the data buffer
        //Serial.print("Raw Data = ");
        //Serial.println(rawData);
        //now find keyword and parse
        char *keywordPointer = strstr(rawData, keyword); //pointer to keyword position

        if (keywordPointer != NULL)
        {
            int dataPosition = (keywordPointer - rawData) + strlen(keyword); //get position after keyword
            char parsedString[40];

            if (strlen(&rawData[dataPosition]) < sizeof(parsedString))
                strlcpy(parsedString, &rawData[dataPosition], sizeof(parsedString));
            else
            {
              strcpy(parsedString, "Token too big");
              Serial.println("Token too big");
            }
            //parsedString[strlen(parsedString)] = NULL;
            //Serial.print("parsedString=");
            //Serial.println(parsedString);
            handleResponse(parsedString);
            //delay(1000);
        }
        else
        {
            Serial.println("sorry no keyword");
        }
    }
}
