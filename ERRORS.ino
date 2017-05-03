/*
    Put here all functions to show errors
    last modification: 02-05-2017
*/

/* errorMSG
 * Return errors messages
 */
 void errorMSG(short code)
{
  char buffer[157];

  digitalWrite(ERRORLED, HIGH); // turn the error led on
  errorFlag = 1;

  switch (code) {
    case 1:
      //do something when var equals 1
      turnAllOff();
      //will store the buffer
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[0]))); // Necessary casts and dereferencing, just copy.
      //lcd.clear(); // clear lcd
      lcd.clear();
      lcd.setCursor(0, 1); // position the cursor to the begining
      lcd.print(buffer);
      lcd.blink();
      delay(1000);


#if (DEBUG == 1)
      Serial.print(buffer);
      Serial.print(F("\n"));
#endif

      break;


    case 2:
      turnAllOff();
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[1]))); // Necessary casts and dereferencing, just copy.
      //lcd.clear(); // clear lcd
      lcd.setCursor(0, 1); // position the cursor to the begining
      lcd.print(buffer);


#if (DEBUG == 1)
      Serial.print(buffer);
      Serial.print(F("\n"));
#endif

      break;

    case 3:

      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[2]))); // Necessary casts and dereferencing, just copy.
      //lcd.clear(); // clear lcd
      lcd.setCursor(1, 0); // position the cursor to the begining
      lcd.print(buffer);


#if (DEBUG == 1)
      Serial.print(buffer);
      Serial.print(F("\n"));
#endif

      break;

  }// end swtich

}// end errorMSG
