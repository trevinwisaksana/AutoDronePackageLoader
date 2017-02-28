/*



*/

/*
int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;

void setup() {
  Serial.begin(115200);
  baseServo.attach(10);
  shoulderServo.attach(9);
  elbowServo.attach(8);
  armServo.attach(7);
  wristServo.attach(6);
  fingerServo.attach(5);
}
*/

/*
void loop() {
  
  if(GamePad.isRedPressed()) {
      count3 += 20;
      if ((count3 <= 180) && (count3 >= 0)) {
         elbowServo.write(count3);
      } else if (count3 >= 180) {
        count3 = 180;
      }
  } else if (GamePad.isBluePressed()) {
      count3 -= 20;
      if ((count3 <= 180) && (count3 >= 0)){
         elbowServo.write(count3);
      }
      else if (count3<=0)
      {
        count3 = 0;
      }
  } else if(GamePad.isOrangePressed()) {
      count4 += 20;
      if ((count4 <= 180) && (count4>=0)){
         armServo.write(count4);
      } else if (count4>=180) {
        count4 = 180;
      }
  } else if (GamePad.isGreenPressed()) {
      count4 -= 20;
      if ((count4<=180) && (count4 >= 0)){
         armServo.write(count4);
      } else if (count4<=0) {
        count4 = 0;
      }
  }

  if(GamePad.isUpPressed()) {
      count5 += 20;
      if ((count5<= 180) && (count2 >= 0)){
         wristServo.write(count5);
      } else if (count5>=180) {
        count5 = 180;
      }

  } else if (GamePad.isDownPressed()) { 
      count5-=20;
      if (count5<=180&&count5>=0){
         baseServo.write(count5);
      }
      else if (count5<=0)
      {
        count5=0;
      }
  
  } else if (GamePad.isRightPressed()) {
      count1+=20;
      if (count1<=180&&count1>=0){
         baseServo.write(count1);
      }
      else if (count1>=180)
      {
        count1=180;
      }
  
  } else if(GamePad.isLeftPressed()) {
      count1-=20;
      if (count1<= 180 && count1 >= 0){
         baseServo.write(count1);
      } else if (count1<=0) {
        count1 = 0;
      }  
  } else {
    baseServo.write(count1);    
    elbowServo.write(count3);
    armServo.write(count4);
    wristServo.write(count5);
  }


  if(AccelerometerSensor.getX() >=3 && AccelerometerSensor.getX()<=9) {
    armServo.write(map(AccelerometerSensor.getX(),3,9,0,180));
  } else if (AccelerometerSensor.getY() >=-3 && AccelerometerSensor.getY()<=3) {
    shoulderServo.write(map(AccelerometerSensor.getY(),-3,3,0,180));
  } else {  
    armServo.write(0);
    shoulderServo.write(0);
  }
  
}
*/
