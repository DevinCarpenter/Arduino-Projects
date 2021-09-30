// Lesson 6 - Parse String by Token
void sixthLesson() {
  char someDataFeed[] = ",SMNMNSG,MSNlsgfflfnDevinONE,2,THREE,4,5.1203";
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
  }
  else {
    Serial.println("NO KEYWORD");  
  }  
}
