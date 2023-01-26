
//===========================================================================================================
// Set LED according to Status Working
//===========================================================================================================
void SetLEDs() {
  //===========================================================================================================
  digitalWrite(pSTAGELED, StageStatus);
  digitalWrite(pMapLED, MapStatus);
  digitalWrite(pExecuteLED, AbortStatus);
  if (ThrottleValue >= 1 && ThrottleValue <= 99) {
    digitalWrite(pMaxThrottleLED, LOW);
    digitalWrite(pMinThrottleLED, LOW);
  }
}
//===========================================================================================================
// Match LED to InGame Status
//===========================================================================================================
void MatchLEDs() {
  digitalWrite(pExecuteLED, Abort_on);
  digitalWrite(pLIGHTSLED, lights_on);
  digitalWrite(pLADDERLED, ladder_on);
  digitalWrite(pSOLARLED, solar_on);
  digitalWrite(pGEARSLED, gears_on);
  digitalWrite(pBRAKESLED, brakes_on);
  digitalWrite(pCHUTESLED, chutes_on);
  digitalWrite(pACTION1LED, action1_on);
  digitalWrite(pACTION2LED, action2_on);
  digitalWrite(pACTION3LED, action3_on);
  digitalWrite(pACTION4LED, action4_on);
}

void UpdateDisplays() {
  //===========================================================================================================
  PanelDisplay();
  //===========================================================================================================
  LeftDisplay();
  //===========================================================================================================
  MiddleDisplay();
  //===========================================================================================================
  RightDisplay();
}

//===========================================================================================================
// Display Selector Working
//===========================================================================================================
void DisplaySelect() {
  //===========================================================================================================
  pDisplayModeState = analogRead(pDisplayMode);  //Read analog value from A5 pin
  switch (pDisplayModeState) {
    case 695 ... 725:
      DisplayValue = 0;
      break;
    case 835 ... 865:
      DisplayValue = 1;
      break;
    case 218 ... 248:
      DisplayValue = 2;
      break;
    case 250 ... 280:
      DisplayValue = 3;
      break;
    case 286 ... 316:
      DisplayValue = 4;
      break;
    case 345 ... 375:
      DisplayValue = 5;
      break;
    case 390 ... 420:
      DisplayValue = 6;
      break;
    case 434 ... 464:
      DisplayValue = 7;
      break;
    case 485 ... 515:
      DisplayValue = 8;
      break;
    case 526 ... 556:
      DisplayValue = 9;
      break;
    case 580 ... 610:
      DisplayValue = 10;
      break;
    case 640 ... 670:
      DisplayValue = 11;
      break;
  }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Initialize the Display's
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void displaysetup() {
  // Start I2C communication with the Multiplexer
  Wire.begin();

  Serial.println("-------------------------------------");
  //===========================================================================================================
  //Duplicate for each display=================================================================================
  //===========================================================================================================
  // Init OLED display on bus number 0 (display 0)
  TCA9548A(0);
  if (!display0.begin(0x3C)) {
    for (;;)
      ;
  }
  // Clear the buffer
  display0.clearDisplay();
  display0.display();
  //===========================================================================================================
  // Init OLED display on bus number 1 (display 1)
  TCA9548A(1);
  if (!display1.begin(0x3C)) {
    for (;;)
      ;
  }
  // Clear the buffer
  display1.clearDisplay();
  display1.display();
  //===========================================================================================================
  // Init OLED display on bus number 2 (display 2)
  TCA9548A(2);
  if (!display2.begin(0x3C)) {
    for (;;)
      ;
  }
  // Clear the buffer
  display2.clearDisplay();
  display2.display();
  //===========================================================================================================
  // Init OLED display on bus number 3 (display 3)
  TCA9548A(3);
  if (!display3.begin(0x3C)) {
    for (;;)
      ;
  }
  // Clear the buffer
  display3.clearDisplay();
  display3.display();
  //===========================================================================================================
  SetLabels();
}
//===========================================================================================================
// Select I2C BUS
//===========================================================================================================
void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
//===========================================================================================================
//==Set Display Labels at start up
//===========================================================================================================
void SetLabels() {
  //===========================================================================================================
  //==Right Display=============================================================================================
  //===========================================================================================================
  TCA9548A(0);  //Make Bus Active
  display0.setTextSize(1);
  display0.setTextColor(WHITE);
  //Display static text
  display0.setCursor(0, 1);  //Line 1
  display0.println("Lights:");
  display0.setCursor(0, 12);  //Line 2
  display0.println("Solar:");
  display0.setCursor(0, 24);  //Line 3
  display0.println("Gears:");
  display0.setCursor(0, 36);  //Line 4
  display0.println("Actn 1:");
  display0.setCursor(0, 48);  //Line 5
  display0.println("Actn 3:");

  display0.setCursor(66, 1);  //Line 1
  display0.println("Ladder:");
  display0.setCursor(66, 12);  //Line 2
  display0.println("Chutes:");
  display0.setCursor(66, 24);  //Line 3
  display0.println("Brakes:");
  display0.setCursor(66, 36);  //Line 4
  display0.println("Actn 2:");
  display0.setCursor(66, 48);  //Line 5
  display0.println("Actn 4:");
  display0.display();
  //===========================================================================================================
  //==Middle Display===========================================================================================
  //===========================================================================================================
  TCA9548A(1);  //Make Bus Active
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(0, 1);  //Line 1
  display1.println("Throttle:");
  display1.setCursor(0, 24);  //Line 3
  display1.println("SAS:");
  display1.setCursor(50, 24);  //Line 4
  display1.println("RCS:");
  display1.drawRect(2, 12, 120, 7, 2);  //Border of the bar chart
  display1.display();
  //===========================================================================================================
  //==Left Display============================================================================================
  //===========================================================================================================
  TCA9548A(2);  //Make Bus Active
  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  //Display static text
  display2.setCursor(0, 0);  //Line 1
  display2.println("SOI:");
  display2.setCursor(0, 10);  //Line 2
  display2.println("Alt:");
  display2.setCursor(0, 20);  //Line 3
  display2.println("APO:");
  display2.setCursor(0, 30);  //Line4
  display2.println("Per:");
  display2.display();
  //===========================================================================================================
  //==Panel Display============================================================================================
  //===========================================================================================================
  TCA9548A(3);  //Make Bus Active
  display3.setTextSize(1);
  display3.setTextColor(WHITE);
  display3.setCursor(0, 1);  //Line 1
  //Display static text
  display3.println("  Kerbal Controller");
  display3.setCursor(0, 12);  //Line 2
  display3.println("       Booting!");
  display3.setCursor(0, 24);  //Line 3
  display3.println("   Data updated at");
  display3.setCursor(0, 36);  //Line 3
  display3.println("       Ship load");
  display3.display();
}
//===========================================================================================================
//==Panel Display============================================================================================
//===========================================================================================================
void PanelDisplay() {
  switch (DisplayValue) {
    case 0:
      TCA9548A(3);  //Make Bus Active
      display3.clearDisplay();
      //display3.fillRect(0, 0, 128, 64, BLACK);  //Clear
      display3.setCursor(1, 0);  //Line 1
      display3.println("  Kerbal Contorller  ");
      display3.setCursor(1, 10);  //Line 2
      display3.println("       Ready      ");
      display3.setCursor(1, 20);  //Line 3
      display3.println("   Have you checked  ");
      display3.setCursor(1, 30);  //Line 4
      display3.println("      Staging?    ");
      display3.setCursor(1, 40);  //Line 5
      display3.println("  Failure is always  ");
      display3.setCursor(1, 50);  //Line 6
      display3.println("     an option!     ");
      display3.display();
      break;
    case 1:
      TCA9548A(3);  //Make Bus Active
      display3.clearDisplay();
      //display3.fillRect(0, 0, 128, 64, BLACK);  //Clear
      display3.setCursor(1, 1);  //Line 1
      display3.println("Solar");
      display3.setCursor(42, 1);  //Line 1 Spaced
      display3.println(solar_on);

      display3.setCursor(1, 12);  //Line 2
      display3.println("Lights");
      display3.setCursor(42, 12);  //Line 2 Spaced
      display3.println(lights_on);

      display3.setCursor(1, 24);  //Line 3
      display3.println("Ladder");
      display3.setCursor(42, 24);  //Line 3 Spaced
      display3.println(ladder_on);

      display3.setCursor(1, 36);  //Line 4
      display3.println("Actn 1");
      display3.setCursor(42, 36);  //Line 4 Spaced
      display3.println(action1_on);

      display3.setCursor(1, 48);  //Line 5
      display3.println("Actn 2");
      display3.setCursor(42, 48);  //Line 5 Spaced
      display3.println(action2_on);

      display3.setCursor(66, 1);  //Line 1-2
      display3.println("Gears");
      display3.setCursor(110, 1);  //Line 1-2 Spaced
      display3.println(gears_on);

      display3.setCursor(66, 12);  //Line 2-2
      display3.println("Brakes");
      display3.setCursor(110, 12);  //Line 2-2 Spaced
      display3.println(brakes_on);

      display3.setCursor(66, 24);  //Line 3-2
      display3.println("Chutes");
      display3.setCursor(110, 24);  //Line 3-2 Spaced
      display3.println(chutes_on);

      display3.setCursor(66, 36);  //Line 4-2
      display3.println("Actn 3");
      display3.setCursor(110, 36);  //Line 4-2 Spaced
      display3.println(action3_on);

      display3.setCursor(66, 48);  //Line 5-2
      display3.println("Actn 4");
      display3.setCursor(110, 48);  //Line 5-2 Spaced
      display3.println(action4_on);

      display3.display();
      break;
    case 2:
      TCA9548A(3);  //Make Bus Active
      display3.clearDisplay();
      //display3.fillRect(0, 0, 128, 64, BLACK);  //Clear
      // display3.display();
      display3.setCursor(0, 0);  //Line 1
      display3.println("Solar  Action Group 9");
      display3.setCursor(0, 9);  //Line 2
      display3.println("Chutes Action Group 8");
      display3.setCursor(0, 18);  //Line 3
      display3.println("Ladder Action Group 7");
      display3.setCursor(0, 27);  //Line 4
      display3.println("Action Group 1");
      display3.setCursor(0, 36);  //Line 5
      display3.println("Action Group 2");
      display3.setCursor(0, 45);  //Line 6
      display3.println("Action Group 3");
      display3.setCursor(0, 54);  //Line 7
      display3.println("Action Group 4");


      display3.display();
      break;
    case 3:
      TCA9548A(3);  //Make Bus Active
      display3.clearDisplay();
      //display3.fillRect(0, 0, 128, 64, BLACK);  //Clear
      // display3.display();
      display3.setCursor(0, 0);  //Line 1
      display3.println("Time it took");
      display3.setCursor(0, 10);  //Line 1
      display3.println(timeItTook);
      display3.setCursor(0, 20);  //Line 1
      display3.println("Start Mills");
      display3.setCursor(0, 30);  //Line 1
      display3.println(startTime);
      display3.setCursor(0, 40);  //Line 1
      display3.println("End Mills");
      display3.setCursor(0, 50);  //Line 1
      display3.println(endTime);
      display3.display();
      break;
  }
}
//===========================================================================================================
//==Left Display=============================================================================================
//===========================================================================================================
void LeftDisplay() {
  TCA9548A(2);  //Make Bus Active
  display2.clearDisplay();
  //display2.fillRect(0, 0, 128, 64, BLACK);  //Clear Display
  display2.setCursor(0, 0);  //Line 1
  display2.println("SOI: ");
  display2.setCursor(42, 0);  //Line 1 Spaced
  //display2.println(strSOI);
  display2.println(SOINameSave);
  display2.setCursor(0, 10);  //Line 2
  display2.println("Alt: ");
  display2.setCursor(42, 10);  //Line 2 Spaced
  display2.println(FormatedAltitude);
  display2.setCursor(0, 20);  //Line 2
  display2.println("APO: ");
  display2.setCursor(42, 20);  //Line 2 Spaced
  display2.println(StateAPO);
  display2.setCursor(0, 30);  //Line 3
  display2.println("PER: ");
  display2.setCursor(42, 30);  //Line 3 Spaced
  display2.println(StatePER);
  display2.display();
}
//===========================================================================================================
//==Middle Display===========================================================================================
//===========================================================================================================
void MiddleDisplay() {
  TCA9548A(1);  //Make Bus Active
  display1.clearDisplay();
  // display1.fillRect(25, 24, 20, 12, BLACK);  //Row 1
  display1.setCursor(0, 24);  //Line 3
  display1.println("SAS:");
  display1.setCursor(24, 24);  //Line 3 Spaced SAS
  if (pSASState == 0) {
    display1.println("OFF");
  } else {
    display1.println("ON ");
  }
  display1.setCursor(50, 24);  //Line 4
  display1.println("RCS:");
  //display1.fillRect(77, 24, 20, 12, BLACK);  //Row 2
  display1.setCursor(76, 24);  //Line 4 Spaced RCS
  if (RCSStatus == 1) {
    display1.println("ON");
  } else {
    display1.println("OFF");
  }

  //         fillRect(x,y,w,z)
  // display1.fillRect(0, 36, 128, 20, BLACK);  //Row 4
  display1.setCursor(0, 36);  //Line 4 Spaced
  if (SasValue == 0) {
    display1.println("STABILITYASSIST");
  }
  if (SasValue == 1) {
    display1.println("PROGRADE");
  }
  if (SasValue == 2) {
    display1.println("RETROGRADE");
  }
  if (SasValue == 3) {
    display1.println("NORMAL");
  }
  if (SasValue == 4) {
    display1.println("ANTINORMAL");
  }
  if (SasValue == 5) {
    display1.println("RADIALIN");
  }
  if (SasValue == 6) {
    display1.println("RADIALOUT");
  }
  if (SasValue == 7) {
    display1.println("TARGET");
  }
  if (SasValue == 8) {
    display1.println("ANTITARGET");
  }
  if (SasValue == 9) {
    display1.println("MANEUVER");
  }
  if (SasValue == 255) {
    display1.println("");
  }
  display1.setCursor(0, 1);  //Line 1
  display1.println("Throttle:");
  // display1.fillRect(5, 13, 116, 5, BLACK);            //Clears the bar depending on the sensor value
  display1.drawRect(2, 12, 120, 7, 2);  //Border of the bar chart
  throttle_valueTemp = (map(ThrottleValue, 0, 1023, 0, 118));
  display1.fillRect(2, 13, throttle_valueTemp, 5, WHITE);  //Draws the bar depending on the sensor value
  display1.display();
}
//===========================================================================================================
//==Right Display============================================================================================
//===========================================================================================================
void RightDisplay() {
  TCA9548A(0);  //Make Bus Active
  display0.clearDisplay();
  // display0.fillRect(42, 0, 20, 64, BLACK);   //Row 1
  // display0.fillRect(110, 0, 20, 64, BLACK);  //Row 2

  display0.setCursor(0, 1);  //Line 1
  display0.println("Lights:");
  display0.setCursor(42, 1);  //Line 1 Spaced
  switch (lights_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(0, 12);  //Line 2
  display0.println("Solar:");
  display0.setCursor(42, 12);  //Line 2 Spaced
  switch (solar_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(0, 24);  //Line 3
  display0.println("Gears:");
  display0.setCursor(42, 24);  //Line 3 Spaced
  switch (gears_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(0, 36);  //Line 4
  display0.println("Actn 1:");
  display0.setCursor(42, 36);  //Line 4 Spaced
  switch (action1_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(0, 48);  //Line 5
  display0.println("Actn 3:");
  display0.setCursor(42, 48);  //Line 5 Spaced
  switch (action3_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(66, 1);  //Line 1
  display0.println("Ladder:");
  display0.setCursor(110, 1);  //Line 1-2 Spaced
  switch (ladder_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(66, 12);  //Line 2
  display0.println("Chutes:");
  display0.setCursor(110, 12);  //Line 2-2 Spaced
  switch (chutes_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(66, 24);  //Line 3
  display0.println("Brakes:");
  display0.setCursor(110, 24);  //Line 3-2 Spaced
  switch (brakes_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(66, 36);  //Line 4
  display0.println("Actn 2:");
  display0.setCursor(110, 36);  //Line 4-2 Spaced
  switch (action2_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }
  display0.setCursor(66, 48);  //Line 5
  display0.println("Actn 4:");
  display0.setCursor(110, 48);  //Line 5-2 Spaced
  switch (action4_on) {
    case 0:
      display0.println("OFF");
      break;
    case 1:
      display0.println("ON ");
      break;
  }

  display0.display();
}