/* 
 *
 */

#include <Servo.h>

// Defining the servo values
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

int pos = 90;              
int increment = 1;        
int updateInterval = 20;      
unsigned long lastUpdate; 


void setup() {

  // Setting the baud rate
  Serial.begin(115200);

  // Setting pin numbers of servos
  baseServo.attach(10);
  shoulderServo.attach(9);
  elbowServo.attach(8);
  armServo.attach(7);
  wristServo.attach(6);
  gripperServo.attach(5);

  // Setup each servo to the middle point
  setServoAngle(SERVO_BASE, 85); // Base
  setServoAngle(SERVO_SHOULDER, 92); // Shoulder
  setServoAngle(SERVO_ELBOW, 94); // Elbow
  setServoAngle(SERVO_ARM, 90); // Arm
  setServoAngle(SERVO_WRIST, 90); // Wrist
  setServoAngle(SERVO_GRIPPER, 90); // Gripper

  testServos();

}

void loop() {
  /* 
    Servo and Angle variables used to 
    store the values of the servo number 
    and the angle it should move to.
  */
  int servo, angle;
  
  // Observes the serial monitor

#ifdef SERIAL_DEBUG
  if scan(&servo, &angle) {
    setServoAngle(servo, angle);
  }
#endif
  updateServos();
   
}

