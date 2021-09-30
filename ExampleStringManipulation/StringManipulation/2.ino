//Lesson 2 - Concatenation
void secondLesson() {
  char stringOne[20] = "123";
  char stringTwo[20] = "456";

  Serial.println(stringOne);//will be 123

  strcat(stringOne, stringTwo); //append stringTwo to stringOne

  Serial.println(stringOne); //will be 123456

  strcat(stringOne, "789");

  Serial.println(stringOne); //will be 123456789

  //In order to avoid a memory overflow on the stringOne[20] or crash of the microcontroller
  // we can do something like this:

  char newString[] = "1234567890";
  if(strlen(newString) + strlen(stringOne) + 1 <= sizeof(stringOne)) { //check if everything fits in stringOne variable; '+ 1' is accounting for EOL
    strcat(stringOne, newString);
    Serial.println(stringOne);//will be a full 19 char 1234567891234567890 +1 for /0
    Serial.print("stringOne Length = ");
    Serial.println(strlen(stringOne));// 19; Add 1 for EOL is 20 bytes total
  }
  else {
    Serial.println("error - too big");
  }
}
