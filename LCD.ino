/*
  Put here all functions related to LCD
  last modification: 02-05-2017
*/

/*  setup_LCD
 *  Configure the lcd
 */

void setup_LCD()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(LCDBL, OUTPUT); // pin of the lED backlight
  digitalWrite(LCDBL,HIGH);
  lcd.print(F("RDMEC"));
  delay(5000); //give time to show the company brand
  
}//end of setup_LCD


/* lcdPrintMenu
   * Show the Menu on LCD
   */
  void lcdPrintMenu(int code)
  {
    switch(code)
    {
      case 1:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("1) Menu ")); 
            lcd.setCursor(0, 1);
            lcd.print(F("AJUSTE RELOGIO "));
            lcd.write(B01111110); //print right arrow
      break;

      case 2:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("2) Menu" )); 
            lcd.setCursor(0, 1);
            lcd.print(F("AJUSTE LIG/DES "));
            lcd.write(B01111110); //print right arrow
      break;

      case 3:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("3) Menu"));
            lcd.setCursor(0, 1);
            lcd.print(F("HORARIO VERAO  "));
            lcd.write(B01111110); //print right arrow
      break;

      case 4:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("4) Menu"));
            lcd.setCursor(0, 1);
            lcd.print(F("SAIR           "));
            lcd.write(B01111110); //print right arrow
      break;

      case 11:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("1.1) Relogio"));
            lcd.setCursor(0, 1);
            lcd.print(F("HORA:         "));
            lcd.print(convertStringTime(actualDateHour));
            //lcd.write(B01111110); //print right arrow
      break;

      case 12:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("1.2) Relogio"));
            lcd.setCursor(0, 1);
            lcd.print(F("MINUTOS:      "));
            lcd.print(convertStringTime(actualDateMinute));
            //lcd.write(B01111110); //print right arrow
      break;

      case 21:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("2.1) Liga/Desl"));
            lcd.setCursor(0, 1);
            lcd.print(F("HORA LIGA:    "));
            lcd.print(convertStringTime(actualTimeOn));
            //lcd.write(B01111110); //print right arrow
      break;

      case 22:
            //lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("2.2) Liga/Desl"));
            lcd.setCursor(0, 1);
            lcd.print(F("HORA DESL:    "));
            lcd.print(convertStringTime(actualTimeOff));
            //lcd.write(B01111110); //print right arrow
      break;

       case 31:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("3.1) Hora Verao"));
            lcd.setCursor(0, 1);
            if(summerTime) lcd.print(F("ATIVADO         "));
            else lcd.print(F("DESATIVADO      "));
         
      break;

      

      
    }//end of switch
    
  }// end of lcdPrintMenu

  
/*  mainInfoLCD
    Function to show the system infos on LCD
     Must show these infos on LCD Display, following this order if any error occour
     Screen1: line1 ->"MODO-HORA"
              line2 ->"(AUTO/MAN)--H:hh:mm'ss"

     Screen2: line1 ->"MEDICOES:-------"
              line2 ->"CORRENTE(A)-DD.D" (SCROLL BETWEEN CURRENT AND VOLTAGE)

     Screen3: line1 ->"LAMPADAS STATUS:"
              line2 ->"LED01:-DESLIGADO" (SCROLL ALL LEDS STATUS)

     Screen4: line1 ->"HORA-LIGA:----HH"
              line2 ->"HORA-DESLIGA:-HH"
  */
void mainInfoLCD(int screenCode)
{

  switch(screenCode)
  {
    case 1:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(F("MODO: "));
          lcd.setCursor(7,0);
          if (autoMode) // check the working mode
          {
            lcd.print(F("      AUTO"));

          }//end if
          else
          {
            lcd.print(F("   MANUAL"));

          }//end else
          
          lcd.setCursor(0, 1);
          lcd.print(F("HORA:      "));
          rtcNow = rtc.now();
          lcd.print(convertStringTime(rtcNow.hour()));
          lcd.print(F(":"));
          lcd.print(convertStringTime(rtcNow.minute()));

     break;

     case 2:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(F("BATERIA: "));
          if(voltageValue >= 24.7) lcd.print(F("     OK"));
          else if(voltageValue < 24.7) lcd.print(F("  BAIXA"));
          lcd.setCursor(0,1);
          lcd.print(F("TENSAO(V):  "));
          lcd.print(voltageValue);
          

     break;

     case 3:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(F("LAMPADAS:1 2 3 4"));
          lcd.setCursor(0,1);
          lcd.print(F("         "));
            if(digitalRead(RELAYPIN1)== RELAYON)lcd.print(F("L "));
            else lcd.print(F("D "));
            if(digitalRead(RELAYPIN2)== RELAYON)lcd.print(F("L "));
            else lcd.print(F("D "));
            if(digitalRead(RELAYPIN3)== RELAYON)lcd.print(F("L "));
            else lcd.print(F("D "));
            if(digitalRead(RELAYPIN4)== RELAYON)lcd.print(F("L "));
            else lcd.print(F("D "));
          
     break;

     case 4:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("HORA LIGA:    "));
          lcd.print(convertStringTime(actualTimeOn));
          lcd.setCursor(0, 1);
          lcd.print(F("HORA DESLIGA: "));
          lcd.print(convertStringTime(actualTimeOff));
     break;

    
          
  }//end of switch

  
  
}//end of mainInfoLCD
