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
  if (pLIGHTSState == 0 && LightsStatus == 0) {
    mySimpit.activateAction(LIGHT_ACTION);
    LightsStatus = 1;
    delay(ButtonDelay);
  } else if (pLIGHTSState == 0 && LightsStatus == 1) {
    mySimpit.deactivateAction(LIGHT_ACTION);
    LightsStatus = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Solar Working
//===========================================================================================================
void Solar() {
  pSOLARState = digitalRead(pSOLAR);
  if (pSOLARState == 0 && SolorStatus == 0) {
    mySimpit.activateCAG(9);
    SolorStatus = 1;
    delay(ButtonDelay);
  } else if (pSOLARState == 0 && SolorStatus == 1) {
    mySimpit.deactivateCAG(9);
    SolorStatus = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Ladder Working
//===========================================================================================================
void Ladder() {
  pLADDERState = digitalRead(pLADDER);
  if (pLADDERState == 0 && LadderStatus == 0) {
    mySimpit.activateCAG(7);
    LadderStatus = 1;
    delay(ButtonDelay);
  } else if (pLADDERState == 0 && LadderStatus == 1) {
    mySimpit.deactivateCAG(7);
    LadderStatus = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Gears Working Transfered
//===========================================================================================================
void Gears() {
  pGEARSState = digitalRead(pGEARS);
  if (pGEARSState == 0 && GearsStatus == 0) {
    mySimpit.activateAction(GEAR_ACTION);
    GearsStatus = 1;
    delay(ButtonDelay);
  } else if (pGEARSState == 0 && GearsStatus == 1) {
    mySimpit.deactivateAction(GEAR_ACTION);
    GearsStatus = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Parking Brakes Working
//===========================================================================================================
void Brakes() {
  pBRAKESState = digitalRead(pBRAKES);
  if (pBRAKESState == 0 && BrakesStatus == 0) {
    mySimpit.activateAction(BRAKES_ACTION);
    BrakesStatus = 1;
    delay(ButtonDelay);
  } else if (pBRAKESState == 0 && BrakesStatus == 1) {
    mySimpit.deactivateAction(BRAKES_ACTION);
    BrakesStatus = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Chutes Working
//===========================================================================================================
void Chutes() {
  pCHUTESState = digitalRead(pCHUTES);
  if (pCHUTESState == 0 && ChutesStatus == 0) {
    mySimpit.activateCAG(8);
    ChutesStatus = 1;
    delay(ButtonDelay);
  } else if (pCHUTESState == 0 && ChutesStatus == 1) {
    mySimpit.deactivateCAG(8);
    ChutesStatus = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Action 1 Working
//===========================================================================================================
void Action1() {
  pACTION1State = digitalRead(pACTION1);
  if (pACTION1State == 0 && Action1Status == 0) {
    mySimpit.activateCAG(1);
    Action1Status = 1;
    delay(ButtonDelay);
  } else if (pACTION1State == 0 && Action1Status == 1) {
    mySimpit.deactivateCAG(1);
    Action1Status = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Action 2 Working
//===========================================================================================================
void Action2() {
  pACTION2State = digitalRead(pACTION2);
  if (pACTION2State == 0 && Action2Status == 0) {
    mySimpit.activateCAG(2);
    Action2Status = 1;
    delay(ButtonDelay);
  } else if (pACTION2State == 0 && Action2Status == 1) {
    mySimpit.deactivateCAG(2);
    Action2Status = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Action 3 Working
//===========================================================================================================
void Action3() {
  pACTION3State = digitalRead(pACTION3);
  if (pACTION3State == 0 && Action3Status == 0) {
    mySimpit.activateCAG(3);
    Action3Status = 1;
    delay(ButtonDelay);
  } else if (pACTION3State == 0 && Action3Status == 1) {
    mySimpit.deactivateCAG(3);
    Action3Status = 0;
    delay(ButtonDelay);
  }
}
//===========================================================================================================
//Action 4 Working
//===========================================================================================================
void Action4() {
  pACTION4State = digitalRead(pACTION4);
  if (pACTION4State == 0 && Action4Status == 0) {
    mySimpit.activateCAG(4);
    Action4Status = 1;
    delay(ButtonDelay);
  } else if (pACTION4State == 0 && Action4Status == 1) {
    mySimpit.deactivateCAG(4);
    Action4Status = 0;
    delay(ButtonDelay);
  }
}