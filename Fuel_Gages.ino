//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Fuel Gauges
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void FuelGages() {
  //Fuel Gauges
  vSF = 100 - 100 * SolidFuel / SolidFuelTot;    //percentage of solid fuel remaining in current stage
  vLF = 100 - 100 * LiquidFuel / LiquidFuelTot;  //percentage of liquid fuel remaining in current stage
  vOX = 100 - 100 * Oxidizer / OxidizerTot;      //percentage of oxidized remaining in current stage
  vEL = 100 * ECharge / EChargeTot;              //percentage of electric charge remaining
  vMP = 100 * MonoProp / MonoPropTot;            //percentage of monopropellant remaining
  /*
  int pMODEValue = digitalRead(pFuelToggle);
  if (pMODEValue == 0) {
  //Fuel Gauges
  vSF = 100 - 100 * SolidFuel / SolidFuelTot;    //percentage of solid fuel remaining in current stage
  vLF = 100 - 100 * LiquidFuel / LiquidFuelTot;  //percentage of liquid fuel remaining in current stage
  vOX = 100 - 100 * Oxidizer / OxidizerTot;      //percentage of oxidized remaining in current stage
  vEL = 100 * ECharge / EChargeTot;              //percentage of electric charge remaining
  vMP = 100 * MonoProp / MonoPropTot;            //percentage of monopropellant remaining
  
  } else {
  //Fuel Gauges
  vSF = 100 - 100 * SolidFuelTot;    //percentage of solid fuel remaining in current stage
  vLF = 100 - 100 * LiquidFuelTot;  //percentage of liquid fuel remaining in current stage
  vOX = 100 - 100 * OxidizerTot;      //percentage of oxidized remaining in current stage
  vEL = 100 * EChargeTot;              //percentage of electric charge remaining
  vMP = 100 * MonoPropTot;            //percentage of monopropellant remaining
  }
  */



  //scale down to 0-9 for binary calculations
  SF = constrain(map(vSF, 0, 100, 0, 10), 0, 10);
  LF = constrain(map(vLF, 0, 100, 0, 10), 0, 10);
  OX = constrain(map(vOX, 0, 100, 0, 10), 0, 10);
  EL = constrain(map(vEL, 0, 100, 0, 10), 0, 10);
  MP = constrain(map(vMP, 0, 100, 0, 10), 0, 10);


  //calculate the power of 2 if not zero. Now each value in binary is all zeroes and a single 1. we can use that to light one LED in each LED bar (dot mode)
  powSF = SolidFuel;
  if (SolidFuel > 0 && SolidFuelTot != 0) {
    //powSF = 0.1 + pow(2, SF);
    powSF = ((int)(pow(2, SF) * 10.0 + 0.5) / 10.0);
    if (SolidFuel >= SolidFuelTot - SolidFuelTot / 100) {
      powSF = ((int)(pow(2, 0) * 10.0 + 0.5) / 10.0);
    }
  } else {
    powSF = 0;
  }
  powLF = LiquidFuel;
  if (LiquidFuel >= LiquidFuelTot / 100 && LiquidFuelTot != 0) {
    //powLF = 0.1 + pow(2, LF);
    powLF = ((int)(pow(2, LF) * 10.0 + 0.5) / 10.0);
    if (LiquidFuel >= LiquidFuelTot - LiquidFuelTot / 100) {
      powLF = ((int)(pow(2, 9) * 10.0 + 0.5) / 10.0);
    }
  } else {
    powLF = 0;
  }
  powOX = Oxidizer;
  if (Oxidizer >= OxidizerTot / 100 && OxidizerTot != 0) {
    //powOX = 0.1 + pow(2, OX);
    powOX = ((int)(pow(2, OX) * 10.0 + 0.5) / 10.0);
    if (Oxidizer >= OxidizerTot - OxidizerTot / 100) {
      powOX = ((int)(pow(2, 0) * 10.0 + 0.5) / 10.0);
    }
  } else {
    powOX = 0;
  }
  powEL = ECharge;
  if (ECharge > 0 && EChargeTot != 0) {
    //powEL = 0.1 + pow(2, EL);
    powEL = ((int)(pow(2, EL) * 10.0 + 0.5) / 10.0);
    if (ECharge >= EChargeTot - EChargeTot / 100) {
      powEL = ((int)(pow(2, 9) * 10.0 + 0.5) / 10.0);
    }
  } else {
    powEL = 0;
  }
  powMP = MonoProp;
  if (MonoProp > 0 && MonoPropTot != 0) {
    //powMP = 0.1 + pow(2, MP);
    powMP = ((int)(pow(2, MP) * 10.0 + 0.5) / 10.0);
    if (MonoProp >= MonoPropTot - MonoPropTot / 100) {
      powMP = ((int)(pow(2, 9) * 10.0 + 0.5) / 10.0);
    }
  } else {
    powMP = 0;
  }


  // keep commented (Original Code)

  //map the 8-bit 595 shift registers to the 10-bit LED bars
  inputBytes[0] = powMP >> 8;
  inputBytes[1] = powMP;
  inputBytes[2] = powEL >> 2;
  inputBytes[3] = (powEL << 6) | (powOX >> 4);
  inputBytes[4] = (powOX << 4) | (powLF >> 6);
  inputBytes[5] = (powLF << 2) | (powSF >> 8);
  inputBytes[6] = powSF;

  /* 
  // keep commented (My Setup Code)
  //map the 8-bit 595 shift registers to the 10-bit LED bars
  inputBytes[0] = powSF >> 8;
  inputBytes[1] = powSF;
  inputBytes[2] = powLF >> 2;
  inputBytes[3] = (powLF << 6) | (powOX >> 4);
  inputBytes[4] = (powOX << 4) | (powEL >> 6);
  inputBytes[5] = (powEL << 2) | (powMP >> 8);
  inputBytes[6] = powMP;
*/

  //prepare the shift register
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);

  //loop through the input bytes
  for (int j = 0; j <= 6; j++) {
    byte inputByte = inputBytes[j];
    // Serial.println(inputByte);
    shiftOut(dataPin, clockPin, MSBFIRST, inputByte);
  }

  //latch the values in when done shifting
  digitalWrite(latchPin, HIGH);
}