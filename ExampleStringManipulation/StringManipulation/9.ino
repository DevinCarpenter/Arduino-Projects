//Lesson 9 - Read from serial and parse out
void ninthLesson() {
  char rawData[100] = ""; //buffer where incoming serial data will be stored
  char keyword[] = "Mydata=";
  Serial.println("Send me data like this. Mydata=test,int,long,float");
  while(1) { //Sets up a loop to be constantly listening for serial data
    if (Serial.available() > 0) { // new data in
      //Read the bytes of Serial data until we hit a newline character or we reach the 
      // buffer limit which is its size (100) minus 1 so we still have room to 
      // add an EOL character. The amount of bytes in the message is returned from the
      // readBytesUntil method.
      size_t byteCount = Serial.readBytesUntil('\n', rawData, sizeof(rawData) -1); //read in data to buffer
      rawData[byteCount] = NULL;//put an end character on the data buffer
      Serial.print("Raw Data = ");
      Serial.println(rawData);

      //now find keyword and parse
      char *keywordPointer = strstr(rawData, keyword); //pointer to keyword position
      if(keywordPointer != NULL) {
        int dataPosition = (keywordPointer - rawData) + strlen(keyword); //get position after keyword

        const char delimeter[] = ",";
        char parsedStrings[4][20]; //4 strings of 20 bytes each
        int dataCount = 0; //Keep track of token count

        //&rawData[dataPosition] represents the address location after the keyword
        char *token = strtok(&rawData[dataPosition], delimeter); //look for first piece of data after keyword until comma
        if(token != NULL && strlen(token) < sizeof(parsedStrings[0])) {
          strncpy(parsedStrings[0], token, sizeof(parsedStrings[0]));
          dataCount++;
        }
        else {
          Serial.println("Token too big");
          strcpy(parsedStrings[0], NULL); //Append EOL to parsed string
        }

        for(int i = 1; i < 4; i++) {
          token = strtok(NULL, delimeter);
          if(token != NULL && strlen(token) < sizeof(parsedStrings[i])) {
            strncpy(parsedStrings[i], token, sizeof(parsedStrings[i]));
            dataCount++;
          }
          else {
            Serial.println("Token too big");
            strcpy(parsedStrings[i], NULL);
          }
        }

        Serial.print("Found ");
        Serial.print(dataCount);
        Serial.println(" strings:");
        for(int i = 0; i < 4; i++)
          Serial.println(parsedStrings[i]);


        //Convert the data to variables we can use
        char theText[20];
        int theInt = 0;
        long theLong = 0;
        float theFloat = 0.0;

        if(dataCount == 4) { //Only proceed if we found four strings
          strncpy(theText, parsedStrings[0], sizeof(theText));
          theInt = atoi(parsedStrings[1]);
          theLong = atol(parsedStrings[2]);
          theFloat = atof(parsedStrings[3]);
          Serial.print("The Text = ");
          Serial.println(theText);
          Serial.print("The Int = ");
          Serial.println(theInt);
          Serial.print("The Long = ");
          Serial.println(theLong);
          Serial.print("The Float = ");
          Serial.println(theFloat);
        }
        else {
          Serial.println("data no good");
        }
      }
      else {
        Serial.println("sorry no keyword");
      }
    }
  }
}
