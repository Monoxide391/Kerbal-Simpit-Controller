//===========================================================================================================
//Stage Button
//===========================================================================================================
void StageButton() {
  StageArmButton();
  pStageState = digitalRead(pSTAGE);
  if (pStageState == 0 && StageStatus == 1) {
    StageMillis = millis();                                  //get the current time
    if (StageMillis - StageStartMillis >= StageMillsPeriod)  //test whether the StageMillsPeriod has elapsed
    {
      mySimpit.activateAction(STAGE_ACTION);
      mySimpit.update();
      StageStartMillis = StageMillis;  //IMPORTANT to update the start time
    }
  }
}
//===========================================================================================================
//Stage Toggle
//===========================================================================================================
void StageArmButton() {
  pStageToggleState = digitalRead(pStageToggle);
  switch (pStageToggleState) {
    case 0:
      digitalWrite(pSTAGELED, HIGH);
      StageStatus = 1;
      break;
    case 1:
      digitalWrite(pSTAGELED, LOW);
      StageStatus = 0;
      break;
  }
}
//===========================================================================================================
//Max Throttle Button Working
//===========================================================================================================
void MaxThrottle() {
  pMaxThrottleValue = digitalRead(pMaxThrottle);
  if (pMaxThrottleValue == 0) {
    digitalWrite(pMaxThrottleLED, HIGH);
    digitalWrite(pMinThrottleLED, LOW);
    digitalWrite(9, HIGH);  // sets the digital pin 13 on
    delay(400);             // waits for a second
    digitalWrite(9, LOW);   // sets the digital pin 13 off
  }
}
//===========================================================================================================
//Min Throttle Button Working
//===========================================================================================================
void MinThrottle() {
  pMinThrottleValue = digitalRead(pMinThrottle);
  if (pMinThrottleValue == 0) {
    digitalWrite(pMinThrottleLED, HIGH);
    digitalWrite(pMaxThrottleLED, LOW);
    digitalWrite(10, HIGH);  // sets the digital pin 13 on
    delay(400);              // waits for a second
    digitalWrite(10, LOW);   // sets the digital pin 13 on
  }
}
//===========================================================================================================
//Map Working
//===========================================================================================================
void Map() {
  pMapState = digitalRead(pMap);
  if (pMapState == 0 && MapStatus == 0) {
    keyboardEmulatorMessage keyMsg(0x4D);
    mySimpit.send(KEYBOARD_EMULATOR, keyMsg);
    MapStatus = 1;
    delay(ButtonDelay);
  } else if (pMapState == 0 && MapStatus == 1) {
    keyboardEmulatorMessage keyMsg(0x4D);
    mySimpit.send(KEYBOARD_EMULATOR, keyMsg);
    MapStatus = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Lights Working
//===========================================================================================================
void Lights() {
  pLIGHTSState = digitalRead(pLIGHTS);
  if (pLIGHTSState == 0) {
    switch (lights_on) {
      case 0:
        mySimpit.activateAction(LIGHT_ACTION);
        break;
      case 1:
        mySimpit.deactivateAction(LIGHT_ACTION);
        break;
    }
  }
}
//===========================================================================================================
//Solar Working
//===========================================================================================================
void Solar() {
  pSOLARState = digitalRead(pSOLAR);
  if (pSOLARState == 0) {
    switch (solar_on) {
      case 0:
        mySimpit.activateCAG(9);
        break;
      case 1:
        mySimpit.deactivateCAG(9);
        break;
    }
  }
}
//===========================================================================================================
//Ladder Working
//===========================================================================================================
void Ladder() {
  pLADDERState = digitalRead(pLADDER);
  if (pLADDERState == 0) {
    switch (ladder_on) {
      case 0:
        mySimpit.activateCAG(7);
        break;
      case 1:
        mySimpit.deactivateCAG(7);
        break;
    }
  }
}
//===========================================================================================================
//Gears Working Transfered
//===========================================================================================================
void Gears() {
  pGEARSState = digitalRead(pGEARS);
  if (pGEARSState == 0) {
    switch (gears_on) {
      case 0:
        mySimpit.activateAction(GEAR_ACTION);
        break;
      case 1:
        mySimpit.deactivateAction(GEAR_ACTION);
        break;
    }
  }
}
//===========================================================================================================
//Parking Brakes Working
//===========================================================================================================
void Brakes() {
  pBRAKESState = digitalRead(pBRAKES);
  if (pBRAKESState == 0) {
    switch (brakes_on) {
      case 0:
        mySimpit.activateAction(BRAKES_ACTION);
        break;
      case 1:
        mySimpit.deactivateAction(BRAKES_ACTION);
        break;
    }
  }
}
//===========================================================================================================
//Chutes Working
//===========================================================================================================
void Chutes() {
  pCHUTESState = digitalRead(pCHUTES);
  if (pCHUTESState == 0) {
    switch (chutes_on) {
      case 0:
        mySimpit.activateCAG(8);
        break;
      case 1:
        mySimpit.deactivateCAG(8);
        break;
    }
  }
}
//===========================================================================================================
//Action 1 Working
//===========================================================================================================
void Action1() {
  pACTION1State = digitalRead(pACTION1);
  if (pACTION1State == 0) {
    switch (action1_on) {
      case 0:
        mySimpit.activateCAG(1);
        break;
      case 1:
        mySimpit.deactivateCAG(1);
        break;
    }
  }
}
//===========================================================================================================
//Action 2 Working
//===========================================================================================================
void Action2() {
  pACTION2State = digitalRead(pACTION2);
  if (pACTION2State == 0) {
    switch (action2_on) {
      case 0:
        mySimpit.activateCAG(2);
        break;
      case 1:
        mySimpit.deactivateCAG(2);
        break;
    }
  }
}
//===========================================================================================================
//Action 3 Working
//===========================================================================================================
void Action3() {
  pACTION3State = digitalRead(pACTION3);
  if (pACTION3State == 0) {
    switch (action3_on) {
      case 0:
        mySimpit.activateCAG(3);
        break;
      case 1:
        mySimpit.deactivateCAG(3);
        break;
    }
  }
}
//===========================================================================================================
//Action 4 Working
//===========================================================================================================
void Action4() {
  pACTION4State = digitalRead(pACTION4);
  if (pACTION4State == 0) {
    switch (action4_on) {
      case 0:
        mySimpit.activateCAG(4);
        break;
      case 1:
        mySimpit.deactivateCAG(4);
        break;
    }
  }
}