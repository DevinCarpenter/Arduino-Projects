// Lesson 4 - String Comparison
void fourthLesson() {

  char stringOne[] = "Test String One";
  char stringTwo[] = "Test String One";

  //
  if(strcmp(stringOne, stringTwo) == 0) {
    Serial.println("THEY ARE EQUAL");
    //run some code here
  }
  else {
    Serial.println("THEY ARE NOT EQUAL");  
  }
}
