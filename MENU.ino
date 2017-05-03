/*
    Put here all functions to deal with the menu
    last modification: 03-05-2017
*/

void menu()
{
  //readButtons();

      #if (DEBUG == 1)
           Serial.print(F("\n\n\n MENU 1: BOTAO PRESS: "));
           Serial.print(buttonPressed);
           Serial.print(F("\n\n\n"));
       #endif
        
  switch(currentMenu)
  {
    /// FIRST LEVEL MENUS
   
        
    case 1: //Adjust clock
        // print
        lcdPrintMenu(1);
      
        
        // check buttons
       // if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U'){currentMenu = currentMenu + 1;}
        if(buttonPressed == 'D'){currentMenu = 4;}
        if(buttonPressed == 'S'){currentMenu = 11;}
      break;
       
     case 2: // Adjust Time On/off
        // print
        //lcdMenuPrint(2);
        lcdPrintMenu(2);
        
        // check buttons
        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U'){currentMenu = currentMenu + 1;}
        if(buttonPressed == 'D'){currentMenu = currentMenu - 1;}
        if(buttonPressed == 'S'){currentMenu = 21;}
      break;

      case 3: // Summer Time
        // print
        //lcdMenuPrint(3);
        lcdPrintMenu(3);
        
        // check buttons
        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U'){currentMenu = currentMenu + 1;}
        if(buttonPressed == 'D'){currentMenu = currentMenu - 1;}
        if(buttonPressed == 'S'){currentMenu = 31;}
      break;

       case 4: // Exit
        // print
        //lcdMenuPrint(4);
        lcdPrintMenu(4);

        // check buttons
        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U'){currentMenu = 1;}
        if(buttonPressed == 'D'){currentMenu = currentMenu - 1;}
        if(buttonPressed == 'S'){currentMenu = 1;goToMenu = false;}
      break;

      // SECOND LEVEL MENUS

      case 11:  // Adjust Hour
            
            //print
            //lcdMenuPrint(11);
            lcdPrintMenu(11);

        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U')
        {
          actualDateHour = actualDateHour + 1;
          if(actualDateHour > MAXHOUR){actualDateHour = MINHOUR;}
          setRtcHour(actualDateHour);
        }
                
        if(buttonPressed == 'D')
        {
          actualDateHour = actualDateHour - 1;
          if(actualDateHour < MINHOUR){actualDateHour = MAXHOUR;}
          setRtcHour(actualDateHour);
        }
        if(buttonPressed == 'S'){currentMenu = 12;}
        
      break;

      case 12:  // Adjust Minute
            
            //print
            //lcdMenuPrint(12);
            lcdPrintMenu(12);

        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U')
        {
          actualDateMinute = actualDateMinute + 1;
          if(actualDateMinute > MAXMINUTE){actualDateMinute = MINMINUTE;} 
          setRtcMin(actualDateMinute);
        }
        if(buttonPressed == 'D')
        {
          actualDateMinute = actualDateMinute - 1;  
          if(actualDateMinute < MINMINUTE){actualDateMinute = MAXMINUTE;}
          setRtcMin(actualDateMinute);
        }
        if(buttonPressed == 'S'){currentMenu = 11;}
        
      break;

      case 21:  // Adjust time On
            
            //print
            //lcdMenuPrint(21);
            lcdPrintMenu(21);

        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U')
        {
          actualTimeOn = actualTimeOn + 1;
          if(actualTimeOn > MAXHOURON){actualTimeOn = MINHOURON;}
        }
        
        if(buttonPressed == 'D')
        {
          actualTimeOn = actualTimeOn - 1;
          if(actualTimeOn < MINHOURON){actualTimeOn = MAXHOURON;}
        }
        
        if(buttonPressed == 'S'){currentMenu = 22;}
        
      break;

     case 22:  // Adjust time Off
            
            //print
            //lcdMenuPrint(22);
            lcdPrintMenu(22);

        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U')
        {
          actualTimeOff = actualTimeOff + 1;
          if(actualTimeOff > MAXHOUROFF){actualTimeOff = MINHOUROFF;}
        }
        
        if(buttonPressed == 'D')
        {
          actualTimeOff = actualTimeOff - 1;
          if(actualTimeOff < MINHOUROFF){actualTimeOff = MAXHOUROFF;}
        }
        if(buttonPressed == 'S'){currentMenu = 21;}
        
      break;

      case 31:  // Adjust summerTime
            
            //print
            //lcdMenuPrint(31);
            lcdPrintMenu(31);

        if(buttonPressed == 'M'){currentMenu = 1; goToMenu = false; }
        if(buttonPressed == 'U'){summerTime = !summerTime;}
        if(buttonPressed == 'D'){summerTime = !summerTime;}
       // if(buttonPressed == 'S'){currentMenu = 1;goToMenu = false;}
        
      break;
      
      
      
  } //end of switch
      
}//end of menu
