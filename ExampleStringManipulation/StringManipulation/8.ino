// Lesson 8 - Passing and returning strings to functions
void passString(char *passedString) {
  Serial.println(passedString);
}

char *giveMeAStringBack() {
  return "something back";  
}
//Pass and return strings
void eighthLesson() {
  
  char someString[] = "I want to pass this";

  passString(someString);

  char newString[20];
  strncpy(newString, giveMeAStringBack(), sizeof(newString));

  Serial.println(newString);
}
