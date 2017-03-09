#include "Servo_Helper.h"

/* List of acceleration and deceleration values */
/* Excel formula count from 0 by 4 to 180 using =INT(5000*(1-(COS(RADIANS(#CELL_COLUMN#))))) */
/* for (int NUMBER = 0; NUMBER <= 100; NUMBER += 1)
 *   accel_table[NUMBER] = INT(5000*(1-(COS(RADIANS(NUMBER)))));
 */


#define SERVOS_STOPPED 0
#define SERVOS_INITIALIZE 1
#define SERVOS_RUNNING 2

int accel_table[101] = {0, 2, 9, 22, 39, 61, 88, 120, 157, 198, 244, 295, 351, 411,
                       475, 544, 618, 696, 778, 864, 954, 1049, 1147, 1249, 1355, 
                       1464, 1577, 1693, 1812, 1935, 2061, 2189, 2320, 2454, 2591, 
                       2730, 2871, 3014, 3159, 3306, 3454, 3605, 3756, 3909, 4063, 
                       4217, 4373, 4529, 4686, 4842, 4999, 5157, 5313, 5470, 5626, 
                       5782, 5936, 6090, 6243, 6394, 6545, 6693, 6840, 6985, 7128, 
                       7269, 7408, 7545, 7679, 7810, 7938, 8064, 8187, 8306, 8422, 
                       8535, 8644, 8750, 8852, 8950, 9045, 9135, 9221, 9303, 9381, 
                       9455, 9524, 9588, 9648, 9704, 9755, 9801, 9842, 9879, 9911, 
                       9938, 9960, 9977, 9990, 9997, 10000};

typedef struct servo_positions_t {
  int time_span;
  int servo_angles[NUMBER_OF_SERVOS];
} servo_positions;

/* Initialize the servo_positions_t struct */
servo_positions myServosPositions[] = { { 3000, {150, 90,  90, 90, 90,  60} }, // Base rotation
                                      { 3000,   {150, 60,  20, 30, 90,  60} }, // Shoulder moves lower
                                      { 2000,   {150, 45,  20, 50, 90,  60} }, // Shoulder moves gripper to position
                                      { 1000,   {150, 35,  20, 50, 90,  85} }, // Gripper grips
                                      { 2000,   {150, 130, 10, 30, 90,  85} }, // Shoulder moves back
                                      { 2000,   { 40, 130, 10, 30, 90,  85} }, // Rotate the base
                                      { 2000,   { 40,  60, 20, 50, 90,  85} }, // Lowers the shoulder
                                      { 2000,   { 40,  10, 90, 90, 90,  85} }, // Position gripper
                                      { 2000,   { 40,  10, 90, 90, 10,  85} }, // Turn gripper
                                      { 1000,   { 40,  10, 90, 90, 10,  60} }, // Release package
                                      { 2000,   { 40,  90, 20, 40, 90,  85} }, // Retract arm
                                      { 2000,   { 40,  90, 90, 90, 90,  85} }, // Slowly move elbow and arm
                                      
                                      { 5000,   {90,  90, 90, 90, 90,  85} }, // Return back to normal position
       
                                      {    0,   {0, 0, 0, 0, 0, 0} } };

/* Initialize the servo_positions_t struct */
servo_positions myServosPositions2[] =  { { 3000, {150,  90,  90, 90, 90,   80} }, // Base rotation
                                        { 3000,   {150,  60,  30, 30, 10,   80} }, // Shoulder moves lower
                                        { 2000,   {150,  35,  30, 50, 10,   80} }, // Shoulder moves gripper to position
                                        { 1000,   {150,  35,  30, 50, 10,  130} }, // Gripper grips
                                        { 2000,   {150, 130,  30, 30, 10,  130} }, // Shoulder moves back
                                        { 2000,   { 40, 130,  30, 30, 10,  130} }, // Rotate the base
                                        { 2000,   { 40,  60,  30, 50, 10,  130} }, // Lowers the shoulder
                                        { 2000,   { 40,  10,  90, 90, 10,  130} }, // Position gripper
                                        { 2000,   { 40,  10,  90, 90, 10,   80} }, // Turn gripper
                                        { 1000,   { 40,  10,  90, 90, 10,   80} }, // Release package
                                        { 2000,   { 40,  30,  40, 60, 10,  130} }, // Retract arm
                                        { 3000,   { 40, 150,  40, 60, 10,  130} }, // Retract shoulder
                                        { 3000,   { 40,  90,  90, 90, 90,  130} }, // Slowly move elbow and arm
                                        { 2000,   { 40,  90,  90, 90, 90,  130} }, // Slowly move elbow and arm
                                        
                                        { 5000,   { 90,  90, 90, 90, 90,   90} }, // Return back to normal position
         
                                        {    0,   {0, 0, 0, 0, 0, 0} } };

servo_positions *pCurrent;
int              servos_step;
int              servos_state = SERVOS_STOPPED;
long             servos_start_time;
long             servos_last_time;
int              servos_start_angle[NUMBER_OF_SERVOS];

void testServos(void) {
  startServoSequence (myServosPositions2);
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
          servo_new_angle = servo_start + (((long)servo_span) * accel_table[percentage]) / 10000L;  // Remove scaling by 10000 here
          setServoAngle(index + 1, servo_new_angle);
          Serial.print(servo_new_angle, DEC);
          Serial.print(" ");          
        }
        Serial.println("done.");
      }
  }
}

