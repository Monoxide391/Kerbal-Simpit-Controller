
//===========================================================================================================
// SAS Button Working
//===========================================================================================================
void Sas() {
  //===========================================================================================================
  //SAS Working
  //===========================================================================================================
  pSASState = digitalRead(pSAS);
  if (pSASState == 1 && SASStatus == 0) {
    mySimpit.activateAction(SAS_ACTION);
    if (SasValue == 255) {
      SASStatus = 1;
    }
  } else if (pSASState == 0 && SASStatus == 1) {
    mySimpit.deactivateAction(SAS_ACTION);
    SASStatus = 0;
  }
  SASSelect();
}
//===========================================================================================================
// SAS Selector Working
//===========================================================================================================
void SASSelect() {
  //===========================================================================================================
  if (pSASState == 1) {
    pSASModeState = analogRead(pSASMode);  //Read analog value from A0 pin
    switch (pSASModeState) {
      case 695 ... 725:
        SasValue = 0;
        //AP_STABILITYASSIST;
        break;
      case 835 ... 865:
        SasValue = 9;
        //AP_MANEUVER;
        break;
      case 218 ... 248:
        SasValue = 1;
        //AP_PROGRADE;
        break;
      case 250 ... 280:
        SasValue = 2;
        //AP_RETROGRADE;
        break;
      case 286 ... 316:
        SasValue = 3;
        //AP_NORMAL;
        break;
      case 345 ... 375:
        SasValue = 4;
        //AP_ANTINORMAL;
        break;
      case 390 ... 420:
        SasValue = 5;
        //AP_RADIALIN;
        break;
      case 434 ... 464:
        SasValue = 6;
        //AP_RADIALOUT;
        break;
      case 485 ... 515:
        SasValue = 7;
        //AP_TARGET;
        break;
      case 526 ... 556:
        SasValue = 8;
        //AP_ANTITARGET;
        break;
      case 580 ... 610:
        // SasValue = 10;
        break;
      case 640 ... 670:
        // SasValue = 11;
        break;
      default:
        SasValue = 255;
        break;
    }
  } else {
    SasValue = 255;
  }
  if (SasValue != 255) {
    SetSASMode();
  }
}
//===========================================================================================================
// Set SAS Mode WOrking
//===========================================================================================================
void SetSASMode() {
  if (SasValue != SasValueTemp && pSASState == 1) {
    mySimpit.setSASMode(SasValue);
    SasValueTemp = SasValue;
  }
}
void Rcs(){
  //===========================================================================================================
  //RCS Working
  //===========================================================================================================
  pRCSState = digitalRead(pRCS);
  if (pRCSState == 1 && RCSStatus == 0) {
    mySimpit.activateAction(RCS_ACTION);
    RCSStatus = 1;
  } else if (pRCSState == 0 && RCSStatus == 1) {
    mySimpit.deactivateAction(RCS_ACTION);
    RCSStatus = 0;
  }
}