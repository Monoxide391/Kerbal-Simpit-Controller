//===========================================================================================================
// Altitude Formatting Working
//===========================================================================================================
void AltitudeFormat() {
  //Altitude
  Altitude = DataAlt;
    String strAlt = "";
  if (Altitude < 1000000 && Altitude > -1000000) {
    strAlt += "m";
    AltitudeCase = 1;
  } else if ((Altitude >= 1000000 && Altitude < 1000000000) || (Altitude <= -1000000 && Altitude > -1000000000)) {
    strAlt += "km";
    AltitudeCase = 2;
  } else if ((Altitude >= 1000000000 && Altitude < 1000000000000) || (Altitude <= -1000000000 && Altitude > -1000000000000)) {
    strAlt += "Mm";
    AltitudeCase = 3;
  } else {
    strAlt += "Gm";
    AltitudeCase = 4;
  }
  switch (AltitudeCase) {
    case 1:
      FormatedAltitude = String(Altitude) + strAlt;
      break;
    case 2:
      Altitude = Altitude / 1000.0;
      FormatedAltitude = String(Altitude) + strAlt;
      break;
    case 3:
      Altitude = Altitude / 1000000.0;
      FormatedAltitude = String(Altitude) + strAlt;
      break;
    case 4:
      Altitude = Altitude / 1000000000.0;
      FormatedAltitude = String(Altitude) + strAlt;
      break;
  }
}