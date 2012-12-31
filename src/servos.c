/*
 * This file is part of Caddy.
 *
 *  Caddy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Caddy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Caddy.  If not, see <http://www.gnu.org/licenses/>.
 */
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
    setServo(PAN, PAN_CENTER + panOffset);
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
    msDelay(1000);
    brake(BOTH);

    // Back and and move back into the corner (help align better)
    moveStraight(-10, 255);
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
    setServo(TILT, TILT_VERT + tiltOffset);
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

    if (servoNum != PAN && servoNum != TILT)
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
