//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Setup Pin modes
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void controlsInit() {
  pinMode(pTHROTTLE, INPUT);
  pinMode(pRX, INPUT);
  pinMode(pRY, INPUT);
  pinMode(pRZ, INPUT);
  pinMode(pTY, INPUT);
  pinMode(pTX, INPUT);
  pinMode(pTZ, INPUT);
  pinMode(pSASMode, INPUT_PULLUP);
  pinMode(pDisplayMode, INPUT_PULLUP);
  pinMode(pTouch, INPUT_PULLUP);
  pinMode(pBUTTONBANK, INPUT_PULLUP);
  pinMode(pLCDx, INPUT_PULLUP);
  pinMode(pPlaneRocket, INPUT_PULLUP);
  pinMode(pTranRot, INPUT_PULLUP);
  pinMode(pRB, INPUT_PULLUP);
  pinMode(pStageToggle, INPUT_PULLUP);
  pinMode(pArmToggle, INPUT_PULLUP);
  pinMode(pFuelToggle, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(pSlideMoterA, OUTPUT);
  pinMode(pSlideMoterB, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(pSAS, INPUT_PULLUP);
  pinMode(pRCS, INPUT_PULLUP);
  pinMode(pSTAGELED, OUTPUT);
  pinMode(pSTAGE, INPUT_PULLUP);
  pinMode(pLIGHTSLED, OUTPUT);
  pinMode(pLIGHTS, INPUT_PULLUP);
  pinMode(pLADDERLED, OUTPUT);
  pinMode(pLADDER, INPUT_PULLUP);
  pinMode(pSOLARLED, OUTPUT);
  pinMode(pSOLAR, INPUT_PULLUP);
  pinMode(pCHUTESLED, OUTPUT);
  pinMode(pCHUTES, INPUT_PULLUP);
  pinMode(pGEARSLED, OUTPUT);
  pinMode(pGEARS, INPUT_PULLUP);
  pinMode(pBRAKESLED, OUTPUT);
  pinMode(pBRAKES, INPUT_PULLUP);
  pinMode(pACTION1LED, OUTPUT);
  pinMode(pACTION1, INPUT_PULLUP);
  pinMode(pACTION2LED, OUTPUT);
  pinMode(pACTION2, INPUT_PULLUP);
  pinMode(pACTION3LED, OUTPUT);
  pinMode(pACTION3, INPUT_PULLUP);
  pinMode(pACTION4LED, OUTPUT);
  pinMode(pACTION4, INPUT_PULLUP);
  pinMode(pACTION5LED, OUTPUT);
  pinMode(pACTION5, INPUT_PULLUP);
  pinMode(pMapLED, OUTPUT);
  pinMode(pMap, INPUT_PULLUP);
  pinMode(pMaxThrottleLED, OUTPUT);
  pinMode(pMaxThrottle, INPUT_PULLUP);
  pinMode(pMinThrottleLED, OUTPUT);
  pinMode(pMinThrottle, INPUT_PULLUP);
  pinMode(pExecuteLED, OUTPUT);
  pinMode(pExecute, INPUT_PULLUP);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Test LEDs Working
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void testLEDS(int testdelay) {

  digitalWrite(pSOLARLED, HIGH);
  digitalWrite(pLADDERLED, HIGH);
  digitalWrite(pLIGHTSLED, HIGH);
  delay(testdelay);
  digitalWrite(pSOLARLED, LOW);
  digitalWrite(pLADDERLED, LOW);
  digitalWrite(pLIGHTSLED, LOW);
  delay(testdelay);
  digitalWrite(pCHUTESLED, HIGH);
  digitalWrite(pBRAKESLED, HIGH);
  digitalWrite(pGEARSLED, HIGH);
  delay(testdelay);
  digitalWrite(pCHUTESLED, LOW);
  digitalWrite(pBRAKESLED, LOW);
  digitalWrite(pGEARSLED, LOW);
  delay(testdelay);
  digitalWrite(pACTION4LED, HIGH);
  digitalWrite(pACTION3LED, HIGH);
  digitalWrite(pACTION2LED, HIGH);
  digitalWrite(pACTION1LED, HIGH);
  delay(testdelay);
  digitalWrite(pACTION4LED, LOW);
  digitalWrite(pACTION3LED, LOW);
  digitalWrite(pACTION2LED, LOW);
  digitalWrite(pACTION1LED, LOW);
  delay(testdelay);
  digitalWrite(pSTAGELED, HIGH);
  digitalWrite(pMapLED, HIGH);
  digitalWrite(pMaxThrottleLED, HIGH);
  digitalWrite(pMinThrottleLED, HIGH);
  digitalWrite(pExecuteLED, HIGH);
  digitalWrite(pExecuteLED, HIGH);
  delay(testdelay);
  digitalWrite(pSTAGELED, LOW);
  digitalWrite(pMapLED, LOW);
  digitalWrite(pMaxThrottleLED, LOW);
  digitalWrite(pMinThrottleLED, LOW);
  digitalWrite(pExecuteLED, LOW);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Step though buttons and switches
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void readswitches() {

  StageArmButton();
  StageButton();
  Throttle();
  Joystick();
  Sas();
  Rcs();
  MinThrottle();
  MaxThrottle();
  Map();
  Lights();
  Solar();
  Ladder();
  Gears();
  Brakes();
  Chutes();
  Action1();
  Action2();
  Action3();
  Action4();
  //SetLEDs();
  MatchLEDs();
  DisplaySelect();
  AltitudeFormat();
  DisplayMillis = millis();                                  //get the current time
  if (DisplayMillis - DisplayStartMillis >= DisplayRefresh)  //test whether the DisplayRefresh has elapsed
  {
    startTime = millis();
    UpdateDisplays();
    endTime = millis();
    timeItTook = endTime - startTime;
    //*-*-*-
    DisplayStartMillis = DisplayMillis;  //IMPORTANT to update the start time
  }

  FuelGages();
}
