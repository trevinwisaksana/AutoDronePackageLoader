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


  SET_SERVO_ANGLE(SERVO_BASE, 87); // Base
  SET_SERVO_ANGLE(SERVO_SHOULDER, 92); // Shoulder
  SET_SERVO_ANGLE(SERVO_ELBOW, 94); // Elbow
  SET_SERVO_ANGLE(SERVO_ARM, 90); // Arm
  SET_SERVO_ANGLE(SERVO_WRIST, 90); // Wrist
  SET_SERVO_ANGLE(SERVO_GRIPPER, 90); // Gripper

}

void loop() {
  int servo, angle;
  
  /* Testing purposes
  // BASE SERVO can only go between 40 - 150
  // SHOULDER SERVO can only go between 90 - 175
  // ELBOW SERVO can only go between 10 - 90
  // ARM SERVO can only go between 60 - 180
  // WRIST SERVO can only go between 0 - 180
  // GRIPPER SERVO can only go between 0 - 40
  */
  // Loading state

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
  }

//  Serial.println("Enter Servo # and Servo Angle #");
  if (scan(&servo, &angle) ) {
     Serial.println("Set Servo");
     SET_SERVO_ANGLE(servo, angle); 
  }

/*
  SET_SERVO_ANGLE(SERVO_BASE, 87); // Base
  SET_SERVO_ANGLE(SERVO_SHOULDER, 92); // Shoulder
  SET_SERVO_ANGLE(SERVO_ELBOW, 94); // Elbow
  SET_SERVO_ANGLE(SERVO_ARM, 90); // Arm
  SET_SERVO_ANGLE(SERVO_WRIST, 90); // Wrist
  SET_SERVO_ANGLE(SERVO_GRIPPER, 90); // Gripper
*/
  
  
  /*
  shoulderServo.write(140);
  
  elbowServo.write(20);
  
  fingerServo.write(30);
  
  armServo.write(130);
  
  fingerServo.write(10);
  
  shoulderServo.write(90);
  
  elbowServo.write(60);
  
  baseServo.write(168); // Base will turn to the other side
  
  shoulderServo.write(90);
  
  elbowServo.write(90);
  
  armServo.write(180);
  
  fingerServo.write(30);
      
     

  baseServo.write(90);
  
  shoulderServo.write(160);
  
  elbowServo.write(90);
  
  armServo.write(180);
  
  wristServo.write(90);
  
  fingerServo.write(10);
  */
}
