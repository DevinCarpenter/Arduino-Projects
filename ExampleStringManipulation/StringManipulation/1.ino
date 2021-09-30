// Lesson 1 - Size, Length and Null
void firstLesson() {
  
  char oneCharacter = 'a';
  Serial.println();
  Serial.print("oneCharacter = ");
  Serial.print(oneCharacter);
  Serial.print(" sizeof=");
  Serial.println(sizeof(oneCharacter));//1

  char charString[] = "123456789"; //Auto added the EOL Null character
  Serial.print("charString[] = ");
  Serial.print(charString);
  Serial.print(" sizeof=");
  Serial.print(sizeof(charString));//10 bc/ End Of Line(EOL) Null character was added on to the end
  Serial.print(" strlen=");
  Serial.println(strlen(charString)); //9 bc EOL not included in length

  char charString2[100]; //Allocation of 100 bytes  for string
  for(int i = 0; i < sizeof(charString2); i++) //Loop through whole character string
    charString2[i] = random(32, 126); //add random ascii to each index

  Serial.print("charString2[100] = ");
  Serial.println(charString2);//garbage; charStrin2 doesn't have an EOL so Serial.print keeps printing what is already stored in memory
  Serial.println(" ");
  Serial.print("sizeof = ");
  Serial.print(sizeof(charString2));//100
  Serial.print(" strlen = ");
  Serial.println(strlen(charString2));//garbage

  char someString[] = "hello world"; //Auto added the EOL Null character
  for(int i = 0; i < strlen(someString); i++)
    charString2[i] = someString[i]; //Doesn't have the EOL because EOL not included in strlen

  Serial.println(charString2);// no null at end
  charString2[strlen(someString)] = NULL; //manually add the EOL to charString at index 11
  Serial.println(charString2);//fixed with null
}
