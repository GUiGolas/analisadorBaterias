/*
    Put here all functions to check user iteractio and idle time
    last modification: 02-05-2017
*/

/* resetIdle
 * turn the idle mode off
 */
void resetIdle()
{
  idleMode = false;
  lastIdle = rtc.now() ;
  if(digitalRead(LCDBL) == LOW)  digitalWrite(LCDBL,HIGH);
  
}//end of resetIdle

/* activateIdle
 * turn the idle mode ON
 */
void activateIdle()
{
  idleMode = true;
  if(digitalRead(LCDBL) == HIGH)  digitalWrite(LCDBL,LOW);
  if(goToMenu == true) goToMenu = false ;
}//end of activate Idle

  
/* checkIdle
 * check if the user its a long time idle
 */
void checkIdle()
{
  // activate the idle mode after one minute off inactivity
  if(idleMode == false){
      rtcNow = rtc.now();
      if( (rtcNow.minute() - lastIdle.minute()) >= 1 )
      {
        activateIdle();
      }//end if
  }//end if idleMode
  
}//end of checkIdle

