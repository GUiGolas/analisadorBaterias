/******************************************************
****      MONITOR DE BATERIA                  ********
*******************************************************
**  AUTHOR:        ********
**  LANGUAGE: ENGLISH(US)                      ********
**  DATE:  02-05-2017                          ********
**  E-MAIL: guilherme@premier24h.com.br        ********
**  VERSION: 3.0                               ********
*******************************************************
*******************************************************
** -------REFERENCES----------                 ********
**                                             ********
**    Arduino SPI                              ********
** http://arduino.cc/en/Reference/SPI          ********
**                                             ********
*******************************************************
*******************************************************
** -------DESCRIPTION----------                ********
** ARDUINO MODEL: MEGA 2560                    ********
** See program description at bottom           ********
*******************************************************
******************************************************/


/// ###########################################################################################
/// ##########################     INICIALIZATION     #########################################
/// ###########################################################################################

// ###################### - INCLUDES - #################################
/* Area to place all include files
include the library code:
*/
#include <Wire.h>  //used to deal with I2C modules
#include "RTClib.h" //used to manage the RTC time module
#include <LiquidCrystal.h> //used to LCD
#include <avr/pgmspace.h> // PROGMEM

// ###################### - DEFINES - #################################
/* Area to place all definitions
 *  
 */

//##  VOLTAGE REFERENCE
#define VOLTAGEREF DEFAULT // Set up the reference for measure the battery voltage
//#define VREFVALUE  5.204 // Set up the reference for measure the battery voltage
#define VREFVALUE  4.9 // Set up the reference for measure the battery voltage
#define VMAX   55.0    // Set up the optimal value of the battery
#define VSMAX  31.0   // Set up the maximum safe voltage
#define VSMIN  22.7   // Set up the maximum safe voltage

//### ANALOG PINS
#define VOLTPIN A2    //pin of the Voltage Sensor
#define LDRPIN A3     //pin of the LDR sensor

//### DIGITAL PINS
//## RELAY PINS
#define RELAYPIN1 28 // pin of Relay 1
#define RELAYPIN2 26 // pin of Relay 2
#define RELAYPIN3 24 // pin of Relay 3
#define RELAYPIN4 22 // pin of Relay 4

// other Relay definitions
#define RELAYMODE OUTPUT //set relay mode
#define RELAYON   LOW     // change if the relay turns on in low voltage
#define RELAYOFF  HIGH    // change if the relay turns off in high voltage

// pins of the MANUAL actvation BUTTONS
#define BUTTONSMODE INPUT_PULLUP
#define BL1PIN  30
#define BL2PIN  32
#define BL3PIN  34
#define BL4PIN  36
// pins of the PUSHBUTTONS input
#define MENUBUTTON  38 // MENU button --- amarelo
#define ENTERBUTTON 40 // ENTERBUTTON
#define PLUSBUTTON  44 // + BUTTON
#define MINUSBUTTON 46 //- BUTTON
// pin of the MODE button
#define MODEBUTTONPIN 42
// buttons define
#define DEBOUNCEDELAY 50 //debeouce delay of 50ms
#define BUTTON_PRESSED LOW

// pin of the error indicator LED
#define ERRORLED 48

// Pins of LCD display
#define LCDRS 19    // A register select (RS) pin that controls where in the LCD's memory you're writing data to.
#define LCDEN 18    // An Enable pin that enables writing to the registers.
#define LCDBL 2   // Activate the LED backlight
// 4 data pins (D4 -D7) -  4bits data display
#define LCDD4 17
#define LCDD5 16
#define LCDD6 15
#define LCDD7 14

//### OTHER DEFINITIONS
//## VOLTAGE LIMITS TO THE LAMPS
#define L1ON  23.8 // voltage to LAMP 01 turn on
#define L1OFF 22.8 // voltage to LAMP 01 turn off
#define L2ON  23.8 // voltage to LAMP 02 turn on
#define L2OFF 22.8 // voltage to LAMP 02 turn off
#define L3ON  23.8 // voltage to LAMP 03 turn on
#define L3OFF 22.8 // voltage to LAMP 03 turn off
#define L4ON  23.8 // voltage to LAMP 04 turn on
#define L4OFF 22.8 // voltage to LAMP 04 turn off

//# ON/OFF LAMP TIME DEFAULT VALUES
#define TIMEON 18 // the lamp will turn on at 18:00 o'clock
#define TIMEOFF 6 // the lamp will turn off at 6:00 o'clock
#define TIMETHRESHOLD 3 //the limit of time

//# INACTIVITY TIME
#define ITIME 100

//# TIME
#define MAXHOUR 23  // 24 hours clock
#define MINHOUR 0
#define MAXMINUTE 59
#define MINMINUTE 0
#define MAXHOURON 21 // superior limit to turn the lghts on
#define MINHOURON 15 // inferior limit to turn the lghts on
#define MAXHOUROFF 9 // superior limit to turn the lghts off
#define MINHOUROFF 5 // inferior limit to turn the lghts off


//# DEBUG SWITCH
// 0 - NOT verbose debug informations on serial/lcd
// 1 - verbose debug informations on serial/lcd
#define DEBUG 0

// ###################### - CONSTANTS - ###################################
// Put all global constants here

//## voltage Sensor
const float voltsPerUnit = 0.004887586; // 5%1023 help to measure the voltage

//## Error messages
// The error messages must be placed as char vectors in the flash memory(PROGMEM) to save "RAM" memory
// All messages must be at maximum 8 chars
// Error message 1
const char error_0[] PROGMEM = "ERR/SENS TENSAO";   // Error caused by a problem while measuring the voltage
// Error message 2
const char error_1[] PROGMEM = "ERR CARTAO SD   ";   // Error while reading/writing SD Card
// Error message 3
const char error_2[] PROGMEM = "ERR RTC         ";   // Error while reading/writing RTC module
// Put other error messages here:

//# Table of strings to be placed on PROGMEM
const char* const string_table[] PROGMEM = {error_0, error_1, error_2}; // don't forget to add all messages here

// ###################### - GLOBAL VARIABLES - ############################
// Put all global variables here

//# error flag variable
bool errorFlag;

//# mode of operation
bool autoMode = false;

//### RTC and Time variables
RTC_DS1307 rtc; //real time clock object
// time variables
byte second = 0;
int second_old = 0;
byte minute = 0;
int minute_old = 0;
int hour = 0;
// conversion to show on LDC
String c_hour = "00";
String c_minute = "00";
String c_second = "00";
//# Current time variable
DateTime rtcNow;

//### Voltage Variables
double voltageValue = 0;

//# User settings variables
bool summerTime = false;
int  actualDateHour = 0;
int  actualDateMinute = 0;
int  actualTimeOn = 18;
int  actualTimeOff = 6;

//## LCD Display object
LiquidCrystal lcd(LCDRS, LCDEN, LCDD4, LCDD5, LCDD6, LCDD7);

//## buttons and menu variables
int currentMenu = 1;
bool goToMenu = false;

//screen rotation
int actualScreen = 1;
int lastScreen = 0;
int lastScreenTime = 0;


//button handlers
char buttonPressed ;
int buttonState[4] = {BUTTON_PRESSED,BUTTON_PRESSED,BUTTON_PRESSED,BUTTON_PRESSED};
int lastButtonState[4] = {BUTTON_PRESSED,BUTTON_PRESSED,BUTTON_PRESSED,BUTTON_PRESSED};
unsigned long lastDebounceTime = 0;

//# idle variables
bool idleMode = false;
DateTime lastIdle ; 

//# ldr variables
bool itsDark = false;
/***************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/


/// ###########################################################################################
/// ##########################          SETUP     #############################################
/// ###########################################################################################
void setup() {

  // ## CONFIGURE THE ACTUATORS
  setup_Actuators(); // configure the relays pins.
  turnAllOff();   // turn all relays off at the beginig to prevent unwanted lights on.]
  
  #if (DEBUG >= 1) // If DEBUG is defined, the Serial verbose is activated
      Serial.begin(9600); // Starts serial ports
      while (!Serial) {
        // wait for serial port to connect. Needed for Leonardo only
      }
      Serial.print(F("\n DEBUG ATIVADO\n"));
  #endif

  

  // ## CONFIGURE THE BUTTONS
  setup_Buttons();
  
  // ## CONFIGURE THE SENSORS
  setup_Sensors();

  //# set the RTC module
  setup_RTC();
  
  // ## CONFIGURE THE LCD
  setup_LCD();
  
  resetIdle();
}

void loop() {
   // #if (DEBUG == 1)
    //  Serial.print(F("\n\n\n INICIO LOOP: \n\n\n"));
    //#endif

  measureVoltage(); //measure the voltage
  #if (DEBUG == 0)
  
      if(voltageValue > VSMIN ){
      
      checkMode();
      rtcNow = rtc.now();
      readButtons();
      if(buttonPressed == 'M') goToMenu = true;
      if(goToMenu) menu();
      else screenRotation();

      errorFlag = 0;
      }//end if  
      else
      {
        errorMSG(1);
      }//end else
  #endif
 
  #if (DEBUG == 1)
  
      checkMode();
      rtcNow = rtc.now();
      readButtons();
      if(buttonPressed == 'M') goToMenu = true;
      if(goToMenu) menu();
      else screenRotation();
      
   #endif
  checkIdle();
  
  //delay(500);
}



/// ###########################################################################################
/// ##########################          END      ##############################################
/// ###########################################################################################

/// ###########################################################################################
