/*
Servo Helper
*/

// Lists the maximum, minimum and middle points of each servo
/*                         base   shoulder elbow  arm    wrist  grip  */
int servo_max[]  = {NULL,  170,   180,     180,   170,   170,   125};
int servo_min[]  = {NULL,  10,    0,       0,     10,    10,    60};
int servo_cen[]  = {NULL,  87,    92,      94,    90,    90,    90};
bool servo_rev[] = {false, false, true,    false, false, false, false};

/* Function to set the servo angle.
 * This function prevents any of the servo's from going
 * beyond its limit.
 */
void SET_SERVO_ANGLE(int servo_number, int servoAngle) {
  // If the servo is somehow reversed, flip the angle 
  // to unreverse the operation
  if (servo_rev[servo_number] == true) {
    servoAngle = 180 - servoAngle;
  }
  /* 
   * If the servo goes beyond the usable angle,
   * set the servo angle to the maximum value 
   */
  if (servoAngle > servo_max[servo_number]) {
    servoAngle = servo_max[servo_number];
  }
  /* If the servo goes lower than the smallest
   * value, then set the angle to the lowest value
   */
  if (servoAngle < servo_min[servo_number]) {
    servoAngle = servo_min[servo_number];
  }
  /* Depending on the servo number (which is defined in the Main),
   * move the specific servo based on the servo angle set.
   */
  switch (servo_number) {
    case 1: 
      baseServo.write(servoAngle);
      break;
    case 2:
      shoulderServo.write(servoAngle);
      break;
    case 3: 
      elbowServo.write(servoAngle);
      break;
    case 4:
      armServo.write(servoAngle);
      break;
    case 5:
      wristServo.write(servoAngle);
      break;
    case 6: 
      gripperServo.write(servoAngle);
      break;
  }
}


