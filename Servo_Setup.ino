/*
Servo Helper
*/

// Lists the maximum and minium points of the servo
//                         base   shoulder elbow  arm    wrist  grip
int servo_max[]  = {NULL,  170,   180,     180,   170,   170,   125};
int servo_min[]  = {NULL,  10,    0,       0,     10,    10,    60};
int servo_cen[]  = {NULL,  87,    92,      94,    90,    90,    90};
bool servo_rev[] = {false, false, true,    false, false, false, false};

void SET_SERVO_ANGLE(int servo_number, int servoAngle) {
  if (servo_rev[servo_number] == true) {
    servoAngle = 180 - servoAngle;
  }
  if (servoAngle > servo_max[servo_number]) {
    servoAngle = servo_max[servo_number];
  }
  if (servoAngle < servo_min[servo_number]) {
    servoAngle = servo_min[servo_number];
  }
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


