/*

Code for servo calibration
by eLab Peers (C) 2014.

Visit us at:
http://www.elabpeers.com

All rights reserved.

Wiring:
For the servo
1. Orange wire on servo to Pin 10
2. Brown wire to GND on Arduino board or both GND on Arduino board and power source
3. Red wire to 5V on Arduino board or + of the power source

Features:
1. The servo moves to 90 degree.
2. 147 == 180 Degrees
3. 65 == 90 Degrees
4.
*/

#include <Servo.h>

Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo armServo;
Servo wristServo;
Servo fingerServo;

void setup()
{
  Serial.begin(9600);
  baseServo.attach(10);
  shoulderServo.attach(9);
  elbowServo.attach(8);
  armServo.attach(7);
  wristServo.attach(6);
  fingerServo.attach(5);
}

void loop()
{
  // BASE SERVO can only go between 10 - 170
  baseServo.write(90); 
  // SHOULDER SERVO can only go between 90 - 175
  shoulderServo.write(90);
  // ELBOW SERVO can only go between 10 - 90
  elbowServo.write(90);
  // ARM SERVO can only go between 60 - 180
  armServo.write(180);
  // WRIST SERVO can only go between 
  wristServo.write(90);
  // FINGER SERVO can only go between 0 - 50
  fingerServo.write(0);
}
