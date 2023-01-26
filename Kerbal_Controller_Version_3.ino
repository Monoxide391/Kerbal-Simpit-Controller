//Alternate Resource Panel. Kerbal Simpit uses ARP for all resource calculations. Without it, the resource level providers won't work at all.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Include these files
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "KerbalSimpit.h"
#include "Arduino.h"
#include <SoftwareSerial.h>
#include <Button.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define SSD1305_NO_SPLASH
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1305 display0(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1305 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1305 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1305 display3(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

KerbalSimpit mySimpit(Serial);  //Establishing a connection to the Plugin
void (*resetFunc)(void) = 0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Arduino Mega Pin Assigments
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//analog pins
const int pTHROTTLE = A0;     //slide pot
const int pRX = A2;           //rotation x-axis
const int pRY = A1;           //rotation y-axis
const int pRZ = A3;           //rotation z-axis
const int pTY = A4;           //translation x-axis
const int pTX = A5;           //translation y-axis
const int pTZ = A6;           //translation z-axis
const int pDisplayMode = A7;  //Display Mode Rotery switch
const int pSASMode = A5;      //SAS Mode Rotery switch
const int pTouch = A4;        //Touch Sensor on Throttle
const int pBUTTONBANK = A15;  //Button switch Bank
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Digital Pins
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const int pLCDx = 0;          //toggle switch
const int pPlaneRocket = 15;  //toggle Plane/Rocket**
const int pTranRot = 2;       //toggle Rotation/Translation**
//const int pTB = 3;          //translation joystick button
const int pRB = 4;               //rotation joystick button**
const int pStageToggle = 5;      //Stage Toggle switch**
const int pArmToggle = 6;        //Arm Toggle switch**
const int pFuelToggle = 7;       //Fuel Gage Toggle**
const int latchPin = 8;          //ST_CP - green Fuel Gages
const int pSlideMoterA = 9;      //L9110H Slide Motor A
const int pSlideMoterB = 10;     //L9110H  Slide Motor B
const int dataPin = 11;          //DS - yellow Fuel Gages
const int clockPin = 12;         //SH_CP - blue Fuel Gages
const int pSAS = 16;             //SAS switch**
const int pRCS = 14;             //RCS switch**
const int pSTAGELED = 22;        //Stage button LED
const int pSTAGE = 23;           //Stage button
const int pLIGHTSLED = 24;       //Lights button LED
const int pLIGHTS = 25;          //Lights button
const int pLADDERLED = 26;       //Ladder button LED
const int pLADDER = 27;          //Ladder button (action group 5)
const int pSOLARLED = 32;        //Solar button LED
const int pSOLAR = 29;           //Solar button (action group 6)
const int pCHUTESLED = 30;       //Chutes button LED
const int pCHUTES = 31;          //Chutes button (action group 7)
const int pGEARSLED = 28;        //Gears button LED
const int pGEARS = 33;           //Gears button
const int pBRAKESLED = 34;       //Brakes button LED
const int pBRAKES = 35;          //Brakes button
const int pACTION1LED = 36;      //Action Group 1 button LED
const int pACTION1 = 37;         //Action Group 1 button
const int pACTION2LED = 38;      //Action Group 2 button LED
const int pACTION2 = 39;         //Action Group 2 button
const int pACTION3LED = 40;      //Action Group 3 button LED
const int pACTION3 = 41;         //Action Group 3 button
const int pACTION4LED = 42;      //Action Group 4 button LED
const int pACTION4 = 43;         //Action Group 4 button
const int pACTION5LED = 44;      //Action Group 5 button LED
const int pACTION5 = 45;         //Action Group 5 button
const int pMapLED = 46;          //Map LED
const int pMap = 47;             //Map Button
const int pMaxThrottleLED = 48;  //Max Throttle LED
const int pMaxThrottle = 49;     //Max Throttle
const int pMinThrottleLED = 50;  //Min Throttle LED
const int pMinThrottle = 51;     //Min Throttle
const int pExecute = 53;         //Abort LED
const int pExecuteLED = 52;      //Abort Button
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//in-game states from Message Handler
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
byte SASval;
byte SASvalOld;
bool refreshSASDisplay = true;  //need bool to force update
bool SAS_on = false;
bool RCS_on = false;
bool Abort_on = false;
bool lights_on = false;
bool ladder_on = false;
bool solar_on = false;
bool gears_on = false;
bool brakes_on = false;
bool chutes_on = false;
bool stage_on = false;
bool action1_on = false;
bool action2_on = false;
bool action3_on = false;
bool action4_on = false;
bool action5_on = false;
bool action6_on = false;
bool inflight = false;
bool inAtmo = false;
long StateAPO = 0;
long StatePER = 0;

//Level Variables
long DataAlt;
long DataRAlt;
String strSOI;
String SOINameSave;
String SOIName;
float IntakeAir;
float IntakeAirTot;
float density;
byte inputBytes[7];
float ECharge;
float EChargeTot;
int EChargeMap;
int powEL = 50;
int vEL = 0;  //Used for Fuel Gauges
int EL = 0;   //Used for Fuel Gauges
float MonoProp;
float MonoPropTot;
int MonoPropMap;
int powMP = 50;
int vMP = 0;  //Used for Fuel Gauges
int MP = 0;   //Used for Fuel Gauges
float LiquidFuel;
float LiquidFuelTot;
int LiquidFuelMap;
int powLF = 50;
int vLF = 0;  //Used for Fuel Gauges
int LF = 0;   //Used for Fuel Gauges
float Oxidizer;
float OxidizerTot;
int OxidizerMap;
int powOX = 50;
int vOX = 0;  //Used for Fuel Gauges
int OX = 0;   //Used for Fuel Gauges
float SolidFuel;
float SolidFuelTot;
int SolidFuelMap;
int powSF = 50;
int vSF = 0;  //Used for Fuel Gauges
int SF = 0;   //Used for Fuel Gauges
float XenonGas;
float XenonGasTot;
int XenonGasMap;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Display's
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int DisplayValue = 0;
int pDisplayModeState = 0;
const int DisplayRefresh = 100;  //refresh Display every 40 ms = 25fps
unsigned long DisplayMillis;
unsigned long DisplayStartMillis;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//SAS & RCS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int pSASState = 0;
int pSASModeState = 0;
int SasValueTemp = 0;
int SasValue = 0;
int SASStatus = 0;
int pRCSState = 0;
int RCSStatus = 0;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Buttons
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int ButtonDelay = 10;
int pStageToggleState = 0;
int pStageState = 0;
unsigned long StageStartMillis;
unsigned long StageMillis;
const unsigned long StageMillsPeriod = 1000;
int pMapState = 0;
int MapStatus = 0;
int pLIGHTSState = 0;
int pSOLARState = 0;
int pLADDERState = 0;
int pGEARSState = 0;
int pBRAKESState = 0;
int pCHUTESState = 0;
int pACTION1State = 0;
int pACTION2State = 0;
int pACTION3State = 0;
int pACTION4State = 0;
int pMaxThrottleValue = 0;
int pMinThrottleValue = 0;
int StageStatus = 0;  // configure this
int AbortStatus = 0;  // configure this
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Throttle and Joystick
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int ThrottleValue = 0;
int ThrottleValueOld = 0;
int throttle_valueTemp = 0;
const int Deadzone = 55;
int yaw = 0;
int reading_yaw = 0;
int roll = 0;
int reading_roll = 0;
int pitch = 0;
int reading_pitch = 0;
int deadRangeLowZR = 0;
int deadRangeHighZR = 0;
int deadRangeLowXR = 0;
int deadRangeHighXR = 0;
int deadRangeLowYR = 0;
int deadRangeHighYR = 0;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Formatted Altitude
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
float Altitude = 0;
int AltitudeCase = 0;
String FormatedAltitude;
String strAlt;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Time Test
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned long startTime;
unsigned long endTime;
unsigned long timeItTook;

void setup() {
  Serial.begin(115200);  // Open the serial connection.
  //Initialize
  controlsInit();  //set all pin modes
  testLEDS(500);   //blink every LED once to test (with a delay of xx ms)
  displaysetup();
  SetDeadZone();
  while (!mySimpit.init())  //Stay in this loop as long as no connection established
  {
    delay(100);
  }
  mySimpit.printToKSP("Connected", PRINT_TO_SCREEN);  // Display a message in KSP to indicate handshaking is complete.
  registerInputchannel();
  StageStartMillis = millis();    //initial start time Stage
  DisplayStartMillis = millis();  //initial start time Display

}

void loop() {
  //reset with buttons
  if (!digitalRead(pACTION1) && !digitalRead(pACTION2) && !digitalRead(pACTION3)) {
    resetFunc();
  }
  mySimpit.update();  // Check for new serial messages
  readswitches();
}
