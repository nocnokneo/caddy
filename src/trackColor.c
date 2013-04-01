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
/** @file */
#include "trackColor.h"
#include "trackLine.h"
#include "camera.h"
#include "servos.h"
#include "junctionCode.h"
#include "motorCntrl.h"
#include "eeProm.h"
#include "helperFunctions.h"

// AVRLIB
#include "rprintf.h"

// avr-libc
#include <stdint.h>
#include <stdbool.h>

// Track the RED ball on black/white background
#define BALL_RMIN    150
#define BALL_RMAX    240
#define BALL_GMIN    16
#define BALL_GMAX    60
#define BALL_BMIN    16
#define BALL_BMAX    50

// Global variables
volatile bool colorStatsProcessed;
bool inSeekPosition;

static uint8_t distToPix( uint8_t distance );

void trackColorInit(int8_t dir)
{
    if (!inSeekPosition)
    {
        brake(BOTH);
        msDelay(200);
        moveStraight(-1 * 0xb, 255);
        inSeekPosition = true;
    }

    // Set pan (center) and tilt
    switch (dir)
    {
    case LOOK_LEFT:
        setServo(PAN, PAN_CENTER + panOffset + PAN_SEEK_OFFSET);
        setServo(TILT, TILT_VERT + tiltOffset);
        break;
    case LOOK_RIGHT:
        setServo(PAN, PAN_CENTER + panOffset - PAN_SEEK_OFFSET);
        setServo(TILT, TILT_VERT + tiltOffset);
        break;
    case LOOK_UP:
        setServo(PAN, PAN_CENTER + panOffset);
        setServo(TILT, TILT_LOOKUP);
        break;
    default:
        break;
    }
    msDelay(500);

    hiResMode();
    rprintf("DS 1 1\r");
    rprintf("LM 0 0\r");

    // Change to poll mode so only one packet is sent
    rprintf("PM 1\r");
}

/*
 * Returns Y1 (top of ball) if camera sees a ball, zero otherwise
 */
uint8_t getBallY( void )
{
    rprintf("lm 0 0\r");

    // Mask everything but the 'My' value
    //rprintf("OM 0 2\r");                             //<- NO MASKING?

    // Change to poll mode so only one packet is sent
    rprintf("PM 1\r");

    // Track red
    rprintf("TC %d %d %d %d %d %d\r",
                    BALL_RMIN, BALL_RMAX, BALL_GMIN, BALL_GMAX, BALL_BMIN, BALL_BMAX);

    colorStatsProcessed = true;
    while (colorStatsProcessed) ;

    return (lineStats[0][Y1_NDX]);
}


bool seeBall( void )
{
   // Track red
   rprintf("TC %d %d %d %d %d %d\r",
           BALL_RMIN, BALL_RMAX, BALL_GMIN, BALL_GMAX, BALL_BMIN, BALL_BMAX);
   colorStatsProcessed = true;
   while (colorStatsProcessed) ;

   return lineStats[0][Y1_NDX] > 0;
}


/*
 * Just does left seeks
 *    PRE - the longest check is the last element of the uncheckedBalls array
 *
 *    uncheckedBalls - ball node numbers and ground distances away from bot
 */
bool cameraSeekLeft( uint8_t uncheckedBalls[][2], uint8_t numUncheckedBalls )
{
    bool foundBall = false;    // Return value
    uint8_t scanHeight = 4;
    uint8_t x = 174;
    //uint8_t ballDist[3];
    //uint8_t ballCount = 0;
    uint8_t scanLimit = distToPix(
                    uncheckedBalls[numUncheckedBalls - 1][BALL_DIST] + 1);

    // get pixel ranges for unchecked balls passed in
    uint8_t i = 0;
    uint8_t maxBallX[3];
    while (i + 1 < numUncheckedBalls)
    {
        maxBallX[i] = (distToPix(uncheckedBalls[i][BALL_DIST]) +
                       distToPix(uncheckedBalls[i + 1][BALL_DIST])) / 2;
        i++;
    }
    maxBallX[i] = scanLimit;

    // scan from small ground distance to large ground distance
    while (x - scanHeight > scanLimit)
    {
        x -= scanHeight;
        setVirtualWindow(x - scanHeight, 1, x, 254);
        if (seeBall())
        {
            foundBall = true;
            //ballDist[ballCount++] = xToDist(x);

            // find ball number of ball at this x
            i = 0;
            while (maxBallX[i] > x)
            {
                i++;
            }
            addToGoalList(uncheckedBalls[i][BALL_NODE_NUM]);

            while (seeBall())
            {
                x -= scanHeight;
                setVirtualWindow(x - scanHeight, 1, x, 254);
            }
        }
    }

    return foundBall;
}

// returns pixel equivalent of 'distance'
static uint8_t distToPix( uint8_t distance )
{
    switch (distance)
    {
    case 0:
    case 1:
        return 174;
    case 2:
        return 0x8d;
    case 3:
        return 0x61;
    case 4:
        return 0x48;
    case 5:
        return 0x36;
    case 6:
        return 0x2b;
    case 7:
        return 0x22;
    case 8:
        return 0x1d;
    case 9:
        return 0x18;
    case 10:
        return 0x14;
    case 11:
        return 0x11;
    case 12:
        return 0x0e;
    default:
        return 0x0;
    }
}

/*
 * Just does right seeks
 *    PRE - the longest check is the last element of the uncheckedBalls array
 *
 *    uncheckedBalls - ball node numbers and ground distances away from bot
 */
bool cameraSeekRight(uint8_t uncheckedBalls[][2], uint8_t numUncheckedBalls)
{
    bool foundBall = false;    // Return value
    uint8_t scanHeight = 4;
    uint8_t x = 0;
    uint8_t scanLimit = 174 - distToPix(
                    uncheckedBalls[numUncheckedBalls - 1][BALL_DIST] + 1);

    // get pixel ranges for unchecked balls passed in
    uint8_t i = 0;
    uint8_t maxBallX[3];
    while (i + 1 < numUncheckedBalls)
    {
        maxBallX[i] = ((174 - distToPix(uncheckedBalls[i][BALL_DIST])) +
                       (174 - distToPix(uncheckedBalls[i + 1][BALL_DIST])))
                       / 2;
        i++;
    }
    maxBallX[i] = scanLimit;

    // scan from small ground distance to large ground distance
    while (x + scanHeight < scanLimit)
    {
        x += scanHeight;
        setVirtualWindow(x, 1, x + scanHeight, 254);
        if (seeBall())
        {
            foundBall = true;
            //ballDist[ballCount++] = xToDist(x);

            // find ball number of ball at this x
            i = 0;
            while (maxBallX[i] < x)
            {
                i++;
            }
            addToGoalList(uncheckedBalls[i][BALL_NODE_NUM]);

            while (seeBall())
            {
                x += scanHeight;
                setVirtualWindow(x, 1, x + scanHeight, 254);
            }
        }
    }

   return foundBall;
}

