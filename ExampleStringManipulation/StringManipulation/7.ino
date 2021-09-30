// Lesson 7 - convert strings to numbers, and numbers to strings
void seventhLesson() {
  char someDataFeed[] = "sgklfjgflgwaasdcDevin-56,1000000,4.57687,text,more text";
  char keyword[] = "Devin";

  char *pointerToFoundData = strstr(someDataFeed, keyword);//Finds keyword within data; returns address if found or null if not found
  if (pointerToFoundData != NULL) { //found keyword
    int positionInString = pointerToFoundData - someDataFeed;
    Serial.print("Keyword Starts at ");
    Serial.println(positionInString);

    //now strip out keyword and junk
    char goodData[50];
    strncpy(goodData, &someDataFeed[positionInString + strlen(keyword)], sizeof(goodData));
    Serial.println(goodData);
    Serial.println();

    //PARSE ** PARSE ** PARSE ** PARSE ** PARSE ** PARSE ** PARSE **
    const char delimeter[] = ",";
    char parsedStrings[5][20]; //contains 5 character strings w/20 bytes per char string
    char *token = strtok(goodData, delimeter); //set pointer to address of first comma
    strncpy(parsedStrings[0], token, sizeof(parsedStrings[0]));//first one
    for(int i = 1; i < 5; i++) {
      token = strtok(NULL, delimeter); //Remembers last location in goodData and starts there.
      if (token == NULL) {
        Serial.print("5 Tokens Expected - Recieved only ");
        Serial.println(i);
      }else {
        strncpy(parsedStrings[i], token, sizeof(parsedStrings[i]));
      }
    }

    for(int i = 0; i < 5; i++)
      Serial.println(parsedStrings[i]);// should have the 5 data strings

    //CONVERT ** CONVERT ** CONVERT ** CONVERT ** CONVERT ** CONVERT ** 
    //data should be an int, long, float, text, text
    int firstInteger = atoi(parsedStrings[0]);
    Serial.println(firstInteger);

    long secondLong = atol(parsedStrings[1]);
    Serial.println(secondLong);

    float thirdFloat = atof(parsedStrings[2]);
    Serial.println(thirdFloat);

    //now to convert everything back into a string
    char newString[100]; //Storage for new string
    char floatValue[5];
    dtostrf(thirdFloat, 1, 2, floatValue);// convert float to str; minimum size of 1 and precision of 2 (rounds to second digit after decimal)
    //sprintf used to build new string with variables
    sprintf(newString, "%s%i,%li,%s,%s,%s", keyword, firstInteger, secondLong, floatValue, parsedStrings[3], parsedStrings[4]);
    Serial.print(newString);
  }
  else {
    Serial.println("NO KEYWORD");  
  }  
}
