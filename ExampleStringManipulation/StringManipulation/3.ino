// Lesson 3 - Copying and Moving Strings
void thirdLesson() {
  char stringOne[20] = "123";
  char stringTwo[20] = "456";
  char stringThree[20] = "1234567891234567890";

  strcpy(stringOne, stringTwo); //replaces stringOne with contents of stringTwo
  //stringOne = stringTwo doesn't work. Must use strcpy

  Serial.println(stringOne); //will be 456

  //replace stringOne with stringTwo with max size of copy equal to stringOne for overflow protection
  strncpy(stringOne, stringThree, sizeof(stringOne)); //overflow protection; doesn't print

  Serial.println(stringOne); //will be 456

  //Protect against overflow and print when string copied is too big
  char someCrazyStringToCopy[] = "whatever you want it to be";
  if(sizeof(someCrazyStringToCopy) <= sizeof(stringOne)) {
    strncpy(stringOne, someCrazyStringToCopy, sizeof(stringOne));
  }
  else {
    Serial.println("That string is too big to copy!");
  }

  //Copy the contents of stringTwo to a certain position of stringOne instead of at beginning
  strncpy(stringOne, "abc", sizeof(stringOne));
  strncpy(stringTwo, "def", sizeof(stringTwo));

  //&stringOne[3] means: Address of stringOne at position3 (after letter c)
  strncpy(&stringOne[3], stringTwo, sizeof(stringOne));

  Serial.println(stringOne); // will be abcdef

  //&stringOne[0] is the literal version of stringOne...stringOne is just a pointer to &stringOne[0]
  // which is why we can use &stringOne[3] to target a specific position of the address to copy to.


  //Moving Strings

  //move some stuff around, swap "abc" with "def"
  strncpy(stringOne, "abcdef", sizeof(stringOne));
  char abc[20];
  strncpy(abc, stringOne, sizeof(abc));//abc has "abcdef"
  abc[3] = NULL;//makes temp "abc"

  char def[20];
  strncpy(def, &stringOne[3], sizeof(def));//pull just def from stringOne

  strncpy(stringOne, def, sizeof(stringOne));//stringOne is "def"
  strncpy(&stringOne[3], abc, sizeof(stringOne));//stringOne is "defabc"

  Serial.println(stringOne);//will be defabc
  

  
}
