/* servos.c
 *
 *    Sets servo positions.
 *        Pan and tilt are usually left on.
 *        Boom, lift, and door are usually left off.
 *
 */

#include "servos.h"

/*
 * Moves servos to initial poistions.
 */
void moveServosToStart(void)
{
#if DEBUGGING
   lcdWriteStr("Servos    ", 0, 6);
#endif
   setServo(PAN, PAN_CENTER+panOffset);
   setServo(TILT, TILT_FORWARD);
   setServo(BOOM, BOOM_UP);
   setServo(DOOR, DOOR_CLOSED);
   myDelay(30);
   setServo(LIFT, LIFT_UP);
   myDelay(50);
   disableServo(BOOM);
   disableServo(DOOR);
   disableServo(LIFT);
}


void grabBonusBall(void)
{
   // Get in position
   // setPose(BB_READY);
   setServo(TILT, TILT_BACK);
   setServo(LIFT, LIFT_BB_READY);
   myDelay(40);
   
   // Drive up to the corner
   forward(BOTH, 255);
   msDelay(800);
   brake(BOTH);
   
   // Back and and move back into the corner (help align better)
   moveStraight(-10,255);
   forward(BOTH, 255);
   msDelay(400);
   brake(BOTH);

   // Execute the pickup sequence
   setServo(BOOM, BOOM_BB_GRAB);
   myDelay(10);
   setServo(TILT, TILT_BB_GRAB);
   myDelay(10);
   setServo(BOOM, BOOM_UP);
   myDelay(10);
   setServo(TILT, TILT_VERT+tiltOffset);
   myDelay(10);
   setServo(LIFT, LIFT_UP);
   
   // Back away from the corner
   moveStraight(-18, 255);
   setServo(TILT, TILT_FORWARD);
   
   disableServo(BOOM);
   disableServo(LIFT);
}


/*
 * Moves servos to desired positions.
 *   Leaves pan and tilt on and saves the position for the debugger.
 *   Keeps servos for door, boom, and lift off.
 *   Moving door, boom, or lift causes delay.
 */
void moveServo(u08 servoNum, u08 servoPos)
{
   setServo(servoNum, servoPos);
   
   if( servoNum != PAN && servoNum != TILT )
   {
      // should delay here (prevents simultaneous movement of some servos)
      disableServo(servoNum);
   }
}

/*
 * Move servo to position and leave it on.
 */
void setServo(u08 servoNum, u08 servoPos)
{
   rprintf("sv %d %d\r", servoNum, servoPos);
}

/*
 * Turn off servo.
 */
void disableServo(u08 servoNum)
{
   rprintf("so %d 0\r", servoNum);
}
