
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Message Handler
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void registerInputchannel()  // Send a message to the plugin registering to channel messages
{
  // Sets our callback function. The KerbalSimpit library will
  // call this function every time a packet is received.
  mySimpit.inboundHandler(messageHandler);
  // Send a message to the plugin registering for the Action status channel.
  // The plugin will now regularly send Action status  messages while the
  // flight scene is active in-game.
  mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);
  mySimpit.registerChannel(CAGSTATUS_MESSAGE);
  mySimpit.registerChannel(SAS_MODE_INFO_MESSAGE);
  mySimpit.registerChannel(FLIGHT_STATUS_MESSAGE);
  mySimpit.registerChannel(ALTITUDE_MESSAGE);
  mySimpit.registerChannel(SOI_MESSAGE);
  mySimpit.registerChannel(ELECTRIC_MESSAGE);
  mySimpit.registerChannel(MONO_MESSAGE);
  mySimpit.registerChannel(LF_MESSAGE);
  mySimpit.registerChannel(OX_MESSAGE);
  mySimpit.registerChannel(SF_MESSAGE);
  mySimpit.registerChannel(XENON_GAS_MESSAGE);
  mySimpit.registerChannel(CUSTOM_RESOURCE_1_MESSAGE);
  mySimpit.registerChannel(ATMO_CONDITIONS_MESSAGE);
  mySimpit.registerChannel(APSIDES_MESSAGE);
}
void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch (messageType) {
    //===========================================================================================================
    case ACTIONSTATUS_MESSAGE:
      if (msgSize == 1) {
        gears_on = msg[0] & GEAR_ACTION;
        brakes_on = msg[0] & BRAKES_ACTION;
        lights_on = msg[0] & LIGHT_ACTION;
        RCS_on = msg[0] & RCS_ACTION;
        SAS_on = msg[0] & SAS_ACTION;
        Abort_on = msg[0] & ABORT_ACTION;
      }
      break;
      //===========================================================================================================
    case CAGSTATUS_MESSAGE:
      if (msgSize == sizeof(cagStatusMessage)) {
        cagStatusMessage cagStatus;
        cagStatus = parseCAGStatusMessage(msg);
        action1_on = cagStatus.is_action_activated(1);
        action2_on = cagStatus.is_action_activated(2);
        action3_on = cagStatus.is_action_activated(3);
        action4_on = cagStatus.is_action_activated(4);
        action5_on = cagStatus.is_action_activated(5);
        action6_on = cagStatus.is_action_activated(6);
        ladder_on = cagStatus.is_action_activated(7);
        chutes_on = cagStatus.is_action_activated(8);
        solar_on = cagStatus.is_action_activated(9);
      }
      break;
      //===========================================================================================================
    case FLIGHT_STATUS_MESSAGE:
      if (msgSize == sizeof(flightStatusMessage)) {
        flightStatusMessage flightStatus;
        flightStatus = parseFlightStatusMessage(msg);
        inflight = flightStatus.isInFlight();
      }
      break;
      //===========================================================================================================
    case ALTITUDE_MESSAGE:
      if (msgSize == sizeof(altitudeMessage)) {
        altitudeMessage myAltitude;
        myAltitude = parseAltitude(msg);
        DataAlt = (long)
          floor(myAltitude.sealevel);
        DataRAlt = (long)
          floor(myAltitude.surface);
      }
      break;
      //===========================================================================================================
    case SOI_MESSAGE:
      SOIName = (char *)msg;
      SOIName[msgSize] = '\0';
      SOINameSave = SOIName;
      break;
      //===========================================================================================================
    case ELECTRIC_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myElectric;
        myElectric = parseResource(msg);
        ECharge = myElectric.available;
        EChargeTot = myElectric.total;
      }
      break;
      //===========================================================================================================
    case MONO_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myMono;
        myMono = parseResource(msg);
        MonoProp = myMono.available;
        MonoPropTot = myMono.total;
      }
      break;
      //===========================================================================================================
    case LF_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myLF;
        myLF = parseResource(msg);
        LiquidFuel = myLF.available;
        LiquidFuelTot = myLF.total;
      }
      break;
      //===========================================================================================================
    case OX_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myOX;
        myOX = parseResource(msg);
        Oxidizer = myOX.available;
        OxidizerTot = myOX.total;
      }
      break;
      //===========================================================================================================
    case SF_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage mySF;
        mySF = parseResource(msg);
        SolidFuel = mySF.available;
        SolidFuelTot = mySF.total;
      }
      break;
      //===========================================================================================================
    case XENON_GAS_MESSAGE:
      if (msgSize == sizeof(resourceMessage)) {
        resourceMessage myXenon;
        myXenon = parseResource(msg);
        XenonGas = myXenon.available;
        XenonGasTot = myXenon.total;
      }
      break;
      //===========================================================================================================
    case CUSTOM_RESOURCE_1_MESSAGE:
      if (msgSize == sizeof(CustomResourceMessage)) {
        CustomResourceMessage myCustom1;
        myCustom1 = parseCustomResource(msg);
        IntakeAir = myCustom1.currentResource1;
        IntakeAirTot = myCustom1.maxResource1;
      }
      break;
      //===========================================================================================================
    case ATMO_CONDITIONS_MESSAGE:
      if (msgSize == sizeof(atmoConditionsMessage)) {
        atmoConditionsMessage myAtmo = parseMessage<atmoConditionsMessage>(msg);
        density = myAtmo.airDensity;
        inAtmo = myAtmo.isVesselInAtmosphere();
      }
      break;
      //===========================================================================================================
    case APSIDES_MESSAGE:
      if (msgSize == sizeof(apsidesMessage)) {
        apsidesMessage myApsides = parseMessage<apsidesMessage>(msg);
        apsidesMessage myApoapsis = parseApsides(msg);
        StateAPO = (long)
          floor(myApoapsis.apoapsis);
        apsidesMessage myPeriapsis = parseApsides(msg);
        StatePER = (long)
          floor(myPeriapsis.periapsis);
        if (StatePER <= 0) {
          StatePER = 0;
        }
      }
      break;


      //===========================================================================================================
    case SAS_MODE_INFO_MESSAGE:  // WORKING
      if (msgSize == sizeof(SASInfoMessage)) {
        SASInfoMessage sasMessage = parseSASInfoMessage(msg);

        switch (sasMessage.currentSASMode) {
          case AP_STABILITYASSIST:
            SasValue = 0;
            break;
          case AP_PROGRADE:
            SasValue = 1;
            break;
          case AP_RETROGRADE:
            SasValue = 2;
            break;
          case AP_NORMAL:
            SasValue = 3;
            break;
          case AP_ANTINORMAL:
            SasValue = 4;
            break;
          case AP_RADIALIN:
            SasValue = 5;
            break;
          case AP_RADIALOUT:
            SasValue = 6;
            break;
          case AP_TARGET:
            SasValue = 7;
            break;
          case AP_ANTITARGET:
            SasValue = 8;
            break;
          case AP_MANEUVER:
            SasValue = 9;
            break;
          default:
            SasValue = 255;
            break;
        }
      }
      break;
  }
}
