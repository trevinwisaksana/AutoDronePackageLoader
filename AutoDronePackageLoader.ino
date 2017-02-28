/*


*/

#include <Servo.h>
#include <math.h>

Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo armServo;
Servo wristServo;
Servo fingerServo;

int baseCount;
int shoulderCount;
int elbowCount;
int armCount;
int wristCount;
int fingerCount;

char fingerState;
char shoulderState;

void setup() {

  // Setting the baud rate
  Serial.begin(9600);

  // Setting pin numbers of servos
  baseServo.attach(10);
  shoulderServo.attach(9);
  elbowServo.attach(8);
  armServo.attach(7);
  wristServo.attach(6);
  fingerServo.attach(5);
 
  // Setup servo states 
  // fingerState = 'U';
  shoulderState = 'H';
 
}

void loop() {
  
  /* Testing purposes
  // BASE SERVO can only go between 10 - 170
  // SHOULDER SERVO can only go between 90 - 175
  // ELBOW SERVO can only go between 10 - 90
  // ARM SERVO can only go between 60 - 180
  // WRIST SERVO can only go between 0 - 180
  // FINGER SERVO can only go between 0 - 40
  */

  switch (shoulderState) {
    case 'S': // STRAIGHT
      shoulderCount = shoulderServo.read();
      if ((shoulderCount > 0) && (shoulderCount < 175)) {
        if (shoulderCount > 90) {
          shoulderCount -= 1;
        } else if (shoulderCount == 90) {
          shoulderCount += 0;
        } else {
          shoulderCount += 1;
        }
        shoulderServo.write(shoulderCount);
      }
      break;
    case 'H': // HIGHEST POINT
      shoulderCount = shoulderServo.read();
      // SHOULDER COUNT CANNOT BE 175 IF ARM SERVO IS NOT 180
      if ((shoulderCount > 0) && (shoulderCount < 91)) {
        shoulderCount += 1;
        shoulderServo.write(shoulderCount);
      }
      break;
  }

  switch (fingerState) {
    case 'G': // GRIP
      // Assigning the fingerCount to its lowest value
      fingerCount = 1;
      // Incrementing the finger count by 1 
      if ((fingerCount > 0) && (fingerCount < 40)) {
        fingerCount += 1;
        fingerServo.write(fingerCount);
      }
      break;
    case 'U': // UNGRIP
      // Assigning the fingerCount to its highest value - 1
      fingerCount = 39;
      if ((fingerCount > 0) && (fingerCount < 40)) {
        fingerCount -= 1;
        fingerServo.write(fingerCount);
      }
      break;
  }
  
}
