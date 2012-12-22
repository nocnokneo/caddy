// servos.h
#ifndef SERVOS_H
#define SERVOS_H

#include "caddy.h"

// Servo numbers ----------------------------------------------------

#define PAN    0
#define TILT   1
#define BOOM   2
#define LIFT   3
#define DOOR   4

#define NUM_SERVOS 5


// Servo positions --------------------------------------------------

#define PAN_CENTER         128 //133
#define MAX_PAN_LEFT       50
#define MAX_PAN_RIGHT      195

#define TILT_BB_GRAB       133
#define TILT_VERT          128   // requires boom to be MAX_UP
#define TILT_BACK          MAX_TILT_BACK
#define TILT_FORWARD       MAX_TILT_FORWARD
#define MAX_TILT_BACK      195
#define MAX_TILT_FORWARD   70

#define BOOM_UP            MAX_BOOM_UP
#define BOOM_BB_GRAB       183   // cup 2.32 inches off ground
#define MAX_BOOM_UP        45
#define MAX_BOOM_DOWN      148

#define LIFT_OPEN          MAX_LIFT_OPEN
#define LIFT_CLOSED        145
#define LIFT_UP            MAX_LIFT_UP
#define LIFT_BB_READY      114   // "V" 3 inces off ground
#define MAX_LIFT_OPEN      183
#define MAX_LIFT_UP        74    // <- increase if lift hits boom on reset

#define DOOR_CLOSED        MAX_DOOR_CLOSED    // touches closed at 73
#define DOOR_OPEN          MAX_DOOR_OPEN
#define MAX_DOOR_CLOSED    71
#define MAX_DOOR_OPEN      200


// Globals ----------------------------------------------------------

#if DEBUGGING
   u08 servoPosition[NUM_SERVOS];
#endif


// Prototypes -------------------------------------------------------

void moveServosToStart(void);
void grabBonusBall(void);
void moveServo(u08 servoNum, u08 servoPos);
void setServo(u08 servoNum, u08 servoPos);
void disableServo(u08 servoNum);


#endif  // #ifndef
