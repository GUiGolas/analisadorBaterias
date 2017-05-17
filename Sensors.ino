/*
    Put here all functions related to SENSORS
    last modification: 02-05-2017
*/

/*  setup_Sensors
 *  configure the sensors
 */
void setup_Sensors()
{
  //# set the VOLTAGE 
  pinMode(VOLTPIN, INPUT);
  //# set the LDR
  pinMode(LDRPIN, INPUT);
  
}//end of setup_Sensors

/*  measureLDR
 *  measure LDR resistance to check if is dark or bright
 *  In this case when it's dark the analog read will return a low value (under 200), when it's bright the analog read will 
 *  return a high value
 */
 void measureLDR()
 {
    int ldrValue;
    for(int i=0; i++; i < 10)
    {
      ldrValue = analogRead(LDRPIN);
      delay(5); // give time for adc;
    }//end for

    ldrValue = ldrValue / 10;
    
    
    if((ldrValue < 200) && (ldrValue > 50)) // if its dark
    {
      itsDark = true;
    }//end if
    else itsDark = false;
    
 }//end of measureLDR

/*  measureVoltage
 *  Function to measure the voltage
 */
 void measureVoltage()
 {
  double adc = 0.00; // analog to digital variable
  double voltage = -1.000;

  //  getting the values
  //  must read several times and get the average
  for (int i = 0; i < 10; i++)
  {
    adc += (double)analogRead(VOLTPIN); //read analog input
    delay(5); // give time for adc;

  }//end for

  adc = adc / 10.0; //  Average

  //converting to analgog
  // USING VREFVALUE AS VOLTAGE REFERENCE
  // VREFVALUE(5.0V)     -            1024
  // voltage             -             adc
  // -------
  // 5.0v(adc) = 1024(voltage)  -->  voltage = 5.0v(adc)/1024.0
  voltage = (VREFVALUE * (double)adc / 1023.9999);

  // now must convert to 24v equivalent
  // voltage = VMAX*voltage/VREFVALUE
  // Exemplo:   voltage = 28.00*voltage/4.9
  voltage = VMAX * voltage / VREFVALUE;

  voltageValue = voltage;
  
 }//end of measureVoltage
