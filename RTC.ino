/*
    Put here all functions to manipulate RTC module
    last modification: 02-05-2017
*/

bool setup_RTC()
{
  //# Try to initialize the module
  if (!rtc.begin())
  {
    errorMSG(3); //RTC module error
  }//end if
  else
  {
    //check if the clock is previously adjusted
    rtcNow = rtc.now();
    if(rtcNow.year()<= 2016) // check the year
    {
      if((rtcNow.hour()<1)&&(rtcNow.minute() < 1))
      {
        rtc.adjust(DateTime(2016, 1, 1, 0, 0, 1));
    delay(10); // Give time to rtc
      }//end if
    }//end if
    
    // Check if the module is running
    if ( !rtc.isrunning())
    {
      errorMSG(3); //RTC module error
    }//end if
    else return true;
    
  }//end else

    return false;
    
}// end of setup_RTC

void setRtcHour(int newHour)
{
  rtcNow = rtc.now();
  int auxMin = rtcNow.minute();
  rtc.adjust(DateTime(2016, 1, 1, newHour, auxMin, 0));

}//end setRtcHour

void setRtcMin(int newMin)
{
  rtcNow = rtc.now();
  int auxHour = rtcNow.hour();
  rtc.adjust(DateTime(2016, 1, 1, auxHour, newMin, 0));

}//end setRtcHour
