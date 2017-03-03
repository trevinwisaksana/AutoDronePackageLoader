/*
Servo Helper
*/

#include "Servo_Helper.h"
// Lists the maximum, minimum and middle points of each servo
/*                         base   shoulder elbow  arm    wrist  grip  */
int servo_max[]  = {NULL,  170,   180,     180,   90,   170,   130};
int servo_min[]  = {NULL,  20,    0,       0,      0,    10,    60};
int servo_cen[]  = {NULL,  85,    92,      94,    90,    90,    90};
bool servo_rev[] = {false, false, true,    false, false, false, false};
int servo_setting[NUMBER_OF_SERVOS + 2];

/* Function to set the servo angle.
 * This function prevents any of the servo's from going
 * beyond its limit.
 */
void setServoAngle(int servo_number, int servo_angle) {
  if ((servo_number <= 0) || (servo_number > NUMBER_OF_SERVOS) ) {
      return;
  }  
  
  /* 
   * If the servo goes beyond the usable angle,
   * set the servo angle to the maximum value 
   */
  if (servo_angle > servo_max[servo_number]) {
    servo_angle = servo_max[servo_number];
  }
  /* If the servo goes lower than the smallest
   * value, then set the angle to the lowest value
   */
  if (servo_angle < servo_min[servo_number]) {
    servo_angle = servo_min[servo_number];
  }

  servo_setting[servo_number] = servo_angle;

  /*If the servo is somehow reversed, flip the angle 
   * to unreverse the operation 
   */
  if (servo_rev[servo_number] == true) {
    servo_angle = 180 - servo_angle;
  }
  
  /* Depending on the servo number (which is defined in the Main),
   * move the specific servo based on the servo angle set.
   */
  switch (servo_number) {
    case 1:
      baseServo.write(servo_angle);
      break;
    case 2:
      shoulderServo.write(servo_angle);
      break;
    case 3: 
      elbowServo.write(servo_angle);
      break;
    case 4:
      armServo.write(servo_angle);
      break;
    case 5:
      wristServo.write(servo_angle);
      break;
    case 6: 
      gripperServo.write(servo_angle);
      break;
  }
}

int getServoAngle(int servoNumber) {
  if ((servoNumber > 0) && (servoNumber <= NUMBER_OF_SERVOS) ) {
    return servo_setting[servoNumber];
  }
  return -1;
}

