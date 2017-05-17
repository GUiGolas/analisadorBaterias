/*
    Put here all utilities functions here
    last modification: 02-05-2016
*/

/*  convertStringTime(int data)
    Function to convert time and data numbers to LCD format, always showing two digits
*/
String convertStringTime(int data)
{
  String aux;
  if (data < 10)
  {
    aux = "0" + String(data);
    return aux;

  }//end if
  else {
    aux = String(data);
    return aux;

  }//end else

}//end of convertString

/*  screenRotation
 *  Function to rotate between the main screens
 */
void screenRotation()
{
  rtcNow = rtc.now();
  int aux = rtcNow.second() - lastScreenTime;
  if(aux < 0) aux = aux * -1;
  if(aux > 9)
  {
    lastScreenTime = rtcNow.second();
    actualScreen = actualScreen +1;
    if(actualScreen > 4) actualScreen = 1;
    
   }//end if
  
  
  if(actualScreen != lastScreen )
  {
    mainInfoLCD(actualScreen);
    lastScreen = actualScreen;
    
  }//end if
  
}//end of screenRotation

/* autoMode()
  * The system will work by itself
  */
void startAutoMode()
  {
    bool activate = false; // to store if the lamps will be activated or not
    //  2.1.2 - Get the current time.
     rtcNow = rtc.now();
     hour = rtcNow.hour();

    // Check the hour to see if its time to turn On
    if(hour >= TIMEON || hour < TIMEOFF )
    {
      activate = true;
    }//end if
    else{
            //  check the threshold
            int aux = TIMEON - hour;
            aux = abs(aux);
        
            int aux2 = hour - TIMEOFF;
            aux2 = abs(aux2);
        
            if ((aux <= TIMETHRESHOLD || aux2 < TIMETHRESHOLD) && itsDark)
            {
              activate = true;
        
            }//end if
    
    }//end else
    //Turn the relays ON/OFF depending of the comparsion.
    if (activate)
    {
      activateRelays(voltageValue);
    }//end if
    else {
      turnAllOff();
    }//end of else
       
  }///end of autoMode

 /* startManualMode
  *  The system will activate the lamps according to the switchs
  *  
  */
void startManualMode()
{
  if (!digitalRead(BL1PIN)) turnOn(1); // THE BUTTONS ARE ACTIVATED ON LOW ENERGY
  else turnOff(1);

  //BUTTON 2
  if (!digitalRead(BL2PIN)) turnOn(2);
  else turnOff(2);

  //BUTTON 3
  if (!digitalRead(BL3PIN)) turnOn(3);
  else turnOff(3);

  //BUTTON 4
  if (!digitalRead(BL4PIN)) turnOn(4);
  else turnOff(4);
  
}//end of startManualMode

/* checkMode
 *  Function to check wich mode the user want to work, manual or automatic
 * 
 */
 void checkMode()
 {
    if(digitalRead(MODEBUTTONPIN) == HIGH)
    {
      autoMode = true;
      startAutoMode();
      }//end if
      else
      {
        autoMode = false;
        startManualMode();
      }//end if
 }//end of checkMode

 
