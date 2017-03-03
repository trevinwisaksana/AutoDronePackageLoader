#include "Servo_Helper.h"

/* List of acceleration and deceleration values */
/* Excel formula count from 0 by 4 to 180 using =INT(90*(1-(COS(RADIANS(#CELL_COLUMN#))))) */
/* for (int NUMBER = 0; NUMBER <= 180; NUMBER += 4)
 *   accel_table[NUMBER / 4] = INT(90*(1-(COS(RADIANS(NUMBER)))));
 */


#define SERVOS_STOPPED 0
#define SERVOS_INITIALIZE 1
#define SERVOS_RUNNING 2
 
int accel_table[46] = {0, 0, 0, 1, 3, 5, 7, 10, 13, 17, 
                      21, 25, 29, 34, 39, 44, 50, 56, 62, 
                      68, 74, 80, 86, 93, 99, 105, 111, 117,
                      123, 129, 134, 140, 145, 150, 154, 158, 
                      162, 166, 169, 172, 174, 176, 178, 179, 
                      179, 180};

typedef struct servo_positions_t {
  int time_span;
  int servo_angles[NUMBER_OF_SERVOS];
} servo_positions;

/* Initialize the servo_positions_t struct */
servo_positions myServosPositions[] = { { 1000, {90, 90, 90, 90, 90, 90} },
                                      { 2000, {170, 90, 90, 90, 120, 60} },
                                      { 1000, {20, 90, 90, 90, 90, 120} },
                                      { 1000, {90, 90, 90, 90, 90, 120} },
                                      {    0, {0, 0, 0, 0, 0, 0} } };

/* Initialize the servo_positions_t struct */
servo_positions myServosPositions2[] = { { 1000, {90, 90, 90, 90, 90, 90} },
                                      { 2000, {120, 120, 120, 120, 120, 120} },
                                      { 3000, {80, 160, 60, 170, 100, 80} },
                                      { 1000, {90, 90, 90, 90, 90, 90} },
                                      {    0, {0, 0, 0, 0, 0, 0} } };

servo_positions *pCurrent;
int              servos_step;
int              servos_state = SERVOS_STOPPED;
long             servos_start_time;
long             servos_last_time;
int              servos_start_angle[NUMBER_OF_SERVOS];

void testServos(void) {
  startServoSequence (myServosPositions);
}

bool startServoSequence (struct servo_positions_t * pSequence) {
  // To prevent running a new sequence before it's finished
  if (servos_state != SERVOS_STOPPED) {
    return false;
  }

  servos_state = SERVOS_RUNNING;
  servos_step = 0;
  pCurrent = (servo_positions *)pSequence;
  servos_start_time = millis();
  servos_last_time = servos_start_time;

  for (int index = 0; index < NUMBER_OF_SERVOS; index++) {
    // Gets the current angle of the servos to initialize the servos
    servos_start_angle[index] = getServoAngle(index + 1);
  }
  return true;
}


bool checkServoRunning (void) {
  if (servos_state == SERVOS_STOPPED) {
    return true;
  }
  return false;
}


void updateServos(void) {
  long new_time;
  long percentage;
  int servo_start, servo_end, servo_span, servo_new_angle;
  
  switch (servos_state) {
    case SERVOS_STOPPED:
      break;
    case SERVOS_INITIALIZE:
      // Change state
      break;
    case SERVOS_RUNNING:
      new_time = millis();
      if ((servos_start_time + (long)(pCurrent[servos_step].time_span)) < new_time) {
        if (pCurrent[servos_step + 1].time_span == 0) {
          Serial.println("SERVOS_STOPPED");
          servos_state = SERVOS_STOPPED;      // might want to write final servo angles here to avoid a timing glitch
          return;
        } else {
          for (int index = 0; index < NUMBER_OF_SERVOS; index++) {
            // Gets the current angle of the servos to initialize the servos
            servos_start_angle[index] = getServoAngle(index + 1);
          }
          servos_step++;
          servos_start_time = new_time;
          servos_last_time  = new_time;
          Serial.print("Next step = ");
          Serial.println(servos_step, DEC);        
        }
      }
      
      if ((servos_last_time + 100) < new_time) {
        servos_last_time = new_time;
        // this is where it gets exciting!!!  Using scaled fractions by multiplying 100
        // this is to prevent dealing with floats (using floats is slow on a microcontroller)
        percentage = (100L * (new_time - servos_start_time)) / (long)(pCurrent[servos_step].time_span);
        Serial.print("Servos moved = ");
        
        for (int index = 0; index < NUMBER_OF_SERVOS; index++) {
          servo_start     = servos_start_angle[index];
          servo_end       = pCurrent[servos_step].servo_angles[index];
          servo_span      = servo_end - servo_start;
          servo_new_angle = servo_start + (((long)servo_span) * percentage) / 100L;  // remove scaling by 100 here
//          setServoAngle(index + 1, servo_new_angle);
//          Serial.print(servo_new_angle, DEC);
//          Serial.print(" ");
          // 
//          Serial.print(percentage, DEC);
//          Serial.print(" ");
          servo_new_angle = servo_start + (((long)servo_span) * (accel_table[(((long)percentage) * 1000L) / 2176L]) ) / 180L;  // remove scaling by 100 here
          setServoAngle(index + 1, servo_new_angle);
          Serial.print(servo_new_angle, DEC);
          Serial.print(" ");          
        }
        Serial.println("done.");
      }
  }
}

