/*
    Put here all functions related to BUTTONS
    last modification: 02-05-2017
*/

/*  setup_Buttons
 *  Configure the buttons
 */
void setup_Buttons()
{
  pinMode(BL1PIN, BUTTONSMODE);
  pinMode(BL2PIN, BUTTONSMODE);
  pinMode(BL3PIN, BUTTONSMODE);
  pinMode(BL4PIN, BUTTONSMODE);

  //# set the push buttons
  pinMode(MENUBUTTON, BUTTONSMODE);
  pinMode(ENTERBUTTON, BUTTONSMODE);
  //# set the + and - buttons
  pinMode(MINUSBUTTON, BUTTONSMODE);
  pinMode(PLUSBUTTON, BUTTONSMODE);
  
  //# set the mode buttons
  pinMode(MODEBUTTONPIN, BUTTONSMODE);
  
}// end of setup_Buttons

/*  readButtons
 *  Reads wich Buttons was pressed
 */
 void readButtons()
 {
    int aux_reading;

  buttonPressed = 'N';
  
  //check the state of each button
  // first button - MENUBUTTON
  aux_reading = readSingleButton(MENUBUTTON,0);
  if(aux_reading == BUTTON_PRESSED)
  {
    buttonPressed = 'M';
    resetIdle(); // if a button is pressed the idle time must be reseted
  }//end if

  // second button - ENTERBUTTON
  aux_reading = readSingleButton(ENTERBUTTON,1);
  if(aux_reading == BUTTON_PRESSED)
  {
    buttonPressed = 'S';
    resetIdle(); // if a button is pressed the idle time must be reseted
  }//end if

  // third button - PLUSBUTTON
  aux_reading = readSingleButton(PLUSBUTTON,2);
  if(aux_reading == BUTTON_PRESSED)
  {
    buttonPressed = 'U';
    resetIdle(); // if a button is pressed the idle time must be reseted
  }//end if

  // third button - MINUSBUTTON
  aux_reading = readSingleButton(MINUSBUTTON,3);
  if(aux_reading == BUTTON_PRESSED)
  {
    buttonPressed = 'D';
    resetIdle(); // if a button is pressed the idle time must be reseted
  }//end if


 }//end of readButtons

 int readSingleButton(int buttonPin, int buttonNumber)
{
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState[buttonNumber]) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCEDELAY) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState[buttonNumber]) {
      buttonState[buttonNumber] = reading;

      }
    }
  

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState[buttonNumber] = reading;
  return lastButtonState[buttonNumber];
  
}//end of readSingleButton
