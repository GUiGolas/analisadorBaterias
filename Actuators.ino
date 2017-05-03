/*
    Put here all functions related to ACTUATORS
    last modification: 02-05-2017
*/

void setup_Actuators()
{
  //# set the LAMPS pins to outoput
  pinMode(RELAYPIN1, RELAYMODE);
  pinMode(RELAYPIN2, RELAYMODE);
  pinMode(RELAYPIN3, RELAYMODE);
  pinMode(RELAYPIN4, RELAYMODE);

  //# set the led pins to output;
  pinMode(ERRORLED, RELAYMODE);
  
}//end of setu_relays

/*  turnAllOff
*   Fucntio to deactivate all lamps for safety or in the begining of the program.
*/
void turnAllOff()
{
  digitalWrite(RELAYPIN1, RELAYOFF); // deactivate relay 1
  digitalWrite(RELAYPIN2, RELAYOFF); // deactivate relay 2
  digitalWrite(RELAYPIN3, RELAYOFF); // deactivate relay 3
  digitalWrite(RELAYPIN4, RELAYOFF); // deactivate relay 4

  digitalWrite(ERRORLED, LOW); // deactivate error led
  
  
}//end of turnAllOff

/* activateRelays
 * Function to compare the measured voltage and activate the correspondent relay
 */
void activateRelays(double voltage)
{

#if (DEBUG > 1)
  Serial.print(F("\n ATUADORES: tensao:  "));
  Serial.print(voltage);

#endif
  //# Relay1
  if (voltage >= L1ON) turnOn(1);
  if (voltage <= L1OFF) turnOff(1);

  //# Relay2
  if (voltage >= L2ON) turnOn(2);
  if (voltage <= L2OFF) turnOff(2);

  //# Relay3
  if (voltage >= L3ON) turnOn(3);
  if (voltage <= L3OFF) turnOff(3);

  //# Relay4
  if (voltage >= L4ON) turnOn(4);
  if (voltage <= L4OFF) turnOff(4);

}//end acrivateRelays

/* turnOn
   Function to give the comand to relay based on the relay code
   Args:
   arg[1] -> code Type: short -> The relay code to be activated. values must be between 1 and 4
*/
void turnOn(short code )
{
  switch (code) {

#if (DEBUG > 1)
      Serial.print(F("\n ATUACAO  "));
      Serial.print(code);

#endif

    case 1:
      if (digitalRead(RELAYPIN1) != RELAYON)
        digitalWrite(RELAYPIN1, RELAYON); // activate relay 1
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n liga led1:  "));


#endif

      break;

    case 2:
      if (digitalRead(RELAYPIN2) != RELAYON)
        digitalWrite(RELAYPIN2, RELAYON); // activate relay 2
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n liga led2:  "));


#endif

      break;

    case 3:
      if (digitalRead(RELAYPIN3) != RELAYON)
        digitalWrite(RELAYPIN3, RELAYON); // activate relay 3
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n liga led3:  "));


#endif

      break;


    case 4:
      if (digitalRead(RELAYPIN4) != RELAYON)
        digitalWrite(RELAYPIN4, RELAYON); // activate relay 4
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n liga led4:  "));


#endif

      break;

  }// end swtich

}//end of turnOn

/* turnOFF
   Function to give the comand to relay based on the relay code
   Args:
   arg[1] -> code Type: short -> The relay code to be deactivated. values must be between 1 and 4
*/
void turnOff(short code)
{

#if (DEBUG > 1)
  Serial.print(F("\n DESATUACAO  "));
  Serial.print(code);

#endif

  switch (code) {
    case 1:
      if (digitalRead(RELAYPIN1) != RELAYOFF)
        digitalWrite(RELAYPIN1, RELAYOFF); // deactivate relay 1
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n desliga led1:  "));


#endif


      break;


    case 2:
      if (digitalRead(RELAYPIN2) != RELAYOFF)
        digitalWrite(RELAYPIN2, RELAYOFF); // deactivate relay 2
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n desliga led2:  "));


#endif


      break;

    case 3:
      if (digitalRead(RELAYPIN3) != RELAYOFF)
        digitalWrite(RELAYPIN3, RELAYOFF); // deactivate relay 3
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n desliga led3:  "));


#endif


      break;


    case 4:
      if (digitalRead(RELAYPIN4) != RELAYOFF)
        digitalWrite(RELAYPIN4, RELAYOFF); // deactivate relay 4
        delay(50);
      // TODO DEBUG MSG
#if (DEBUG > 1)
      Serial.print(F("\n desliga led4:  "));


#endif


      break;

  }// end swtich


}// end turnOff

