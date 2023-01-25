
//===========================================================================================================
// Throttle Working
//===========================================================================================================
void Throttle() {
  //===========================================================================================================
  throttleMessage throttle_msg;
  // Read the value of the potentiometer
  ThrottleValue = analogRead(pTHROTTLE);
  // Convert it in KerbalSimpit Range
  throttle_msg.throttle = map(ThrottleValue, 0, 1023, 0, INT16_MAX);
  // Send the message
  //if (ThrottleValue != ThrottleValueOld) {
    mySimpit.send(THROTTLE_MESSAGE, throttle_msg);
  //  ThrottleValueOld = ThrottleValue;
 //}
}
//===========================================================================================================
// Rotation Joystick Working
//===========================================================================================================
void Joystick() {
  rotationMessage rot_msg;
  // Read the values of the potentiometers
  reading_pitch = analogRead(pRX);
  reading_roll = analogRead(pRZ);
  reading_yaw = analogRead(pRY);

  // Check if they are in the deadzone, if not, set the values to a KSP Figure
  // Pitch

  if (reading_pitch < deadRangeLowXR) {
    pitch = map(reading_pitch, 0, deadRangeLowXR, INT16_MIN, 0);
  } else if (reading_pitch > deadRangeHighXR) {
    pitch = map(reading_pitch, deadRangeHighXR, 1023, 0, INT16_MAX);
  } else pitch = 0;

  // Roll

  if (reading_roll < deadRangeLowZR) {
    roll = map(reading_roll, 0, deadRangeLowZR, INT16_MIN, 0);
  } else if (reading_roll > deadRangeHighZR) {
    roll = map(reading_roll, deadRangeHighZR, 1023, 14, INT16_MAX);
  } else roll = 0;
  // Yaw

  if (reading_yaw < deadRangeLowYR) {
    yaw = map(reading_yaw, 0, deadRangeLowYR, INT16_MIN, 0);
  } else if (reading_yaw > deadRangeHighYR) {
    yaw = map(reading_yaw, deadRangeHighYR, 1023, 0, INT16_MAX);
  } else yaw = 0;
  //Send message if any value changed
  if (pitch >= 0 || roll >= 0 || yaw >= 0) {
    // Put those values in the message
    rot_msg.setPitch(pitch);
    rot_msg.setRoll(roll);
    rot_msg.setYaw(yaw);
    // Send the message
    mySimpit.send(ROTATION_MESSAGE, rot_msg);
  }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// AutoSet Deadzones for Joysticks
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetDeadZone() {
  reading_pitch = analogRead(pRX);
  reading_roll = analogRead(pRZ);
  reading_yaw = analogRead(pRY);
  deadRangeLowXR = reading_pitch - Deadzone;
  deadRangeHighXR = reading_pitch + Deadzone;
  deadRangeLowZR = reading_roll - Deadzone;
  deadRangeHighZR = reading_roll + Deadzone;
  deadRangeLowYR = reading_yaw - Deadzone;
  deadRangeHighYR = reading_yaw + Deadzone;
}