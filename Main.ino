/*


*/

#include <Servo.h>
#include <math.h>
#define SERVO_BASE     1
#define SERVO_SHOULDER 2
#define SERVO_ELBOW    3
#define SERVO_ARM      4
#define SERVO_WRIST    5
#define SERVO_GRIPPER  6

Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo armServo;
Servo wristServo;
Servo gripperServo;

int baseCount;
int shoulderCount;
int elbowCount;
int armCount;
int wristCount;
int gripperCount;

char gripperState;
char shoulderState;
char elbowState;
char testingState;

unsigned long previousMillis = 0;
const long interval = 50;

void setup() {

  // Setting the baud rate
  Serial.begin(9600);

  // Setting pin numbers of servos
  baseServo.attach(10);
  shoulderServo.attach(9);
  elbowServo.attach(8);
  armServo.attach(7);
  wristServo.attach(6);
  gripperServo.attach(5);

  // Setup each servo to the middle point
  SET_SERVO_ANGLE(SERVO_BASE, 87); // Base
  SET_SERVO_ANGLE(SERVO_SHOULDER, 92); // Shoulder
  SET_SERVO_ANGLE(SERVO_ELBOW, 94); // Elbow
  SET_SERVO_ANGLE(SERVO_ARM, 90); // Arm
  SET_SERVO_ANGLE(SERVO_WRIST, 90); // Wrist
  SET_SERVO_ANGLE(SERVO_GRIPPER, 90); // Gripper

}

void loop() {
  /* 
    Servo and Angle variables used to 
    store the values of the servo number 
    and the angle it should move to.
  */
  int servo, angle;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
  }

  // Scan observes the Serial monitor for values
  if (scan(&servo, &angle) ) {
     Serial.println("Set Servo");
     SET_SERVO_ANGLE(servo, angle); 
  }

}
