// Lesson 5 - Finding and Parsing Strings
void fifthLesson() {
  char someDataFeed[] = ",SMNMNSG,MSNlsgfflfnDevin12345"; //garbage in string to parse through
  char keyword[] = "Devin";

  char *pointerToFoundData = strstr(someDataFeed, keyword);//Finds keyword within data; returns address if found or null if not found
  if (pointerToFoundData != NULL) { //found keyword
    int positionInString = pointerToFoundData - someDataFeed;
    Serial.print("Keyword Starts at ");
    Serial.println(positionInString);

    //now strip out keyword and junk
    char goodData[20];
    strncpy(goodData, &someDataFeed[positionInString + strlen(keyword)], sizeof(goodData));
    Serial.println(goodData);
  }
  else {
    Serial.println("NO KEYWORD");  
  }
}
