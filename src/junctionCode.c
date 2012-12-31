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
/* junctionCode.c
 *
 *   Actions that occur at junctions.
 *
 *   (Pass by reference causes error.) -Logan
 */

#include "junctionCode.h"


// initialized in initBotGlobals
BOOL checkedList[] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                       FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                       FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                       FALSE, FALSE, FALSE };
// initialized in initBotGlobals
u08 goalList[NUM_GOALS];

/*
 * Searches for ground balls, picks-up bonous balls, and computes best path.
 */
void junctionCode(void)
{
    BOOL foundBall = FALSE;

    switch (botNode)
    {
    case (0):                     // old virtual windowing look for ball 7 and 8
        foundBall = nodeCode0();
        break;
    case (21):                          // Suppress standard seek, should already
        break;                          // skip junction code at this node
    case (22):
        foundBall = standardBallSearch();  // standard seek and
        foundBall |= nodeCode22();         // tilt look for ball 9, 11, and 12
        break;
    case (31):                           // rotate bot for diagonal ball search
    case (34):                           // from any heading at node 31 or 34
        foundBall = diagNodeCode();
        break;
    case (37):                            // seek for top balls from nest sensor
        if (numKnownGoals < NUM_GOALS && (!checkedList[13] || !checkedList[17]))
        {
            botNode = 35;
            moveStraight(10, 255);
            foundBall = diagNodeCode();
            moveStraight(-10, 255);
            botNode = 37;

            //pathList[pathListIndex--] = 36;
            //pathList[pathListIndex--] = 35;
        }
        break;
    default:
        foundBall = standardBallSearch();
        break;
    }

    if (foundBall)
    {
        // clear checked list, if last ball found
        if (numKnownGoals == NUM_GOALS)
        {
            u08 i;
            for (i = 0; i < NUM_BALL_NODES + 1; i++)
            {
                checkedList[i] = TRUE;
            }
        }
        updatePath();
        printGoalList();
    }
}


/*
 * Returns true if a ball is found and the goal list is updated
 */
BOOL standardBallSearch( void )
{
    NODE curNode;
    NODE nextNode;
    u08 nextNodeNum;
    s08 lookDir = -1;                   // look left first
    s08 hallHeading = 0;
    u08 ballDist = 0;
    u08 uncheckedBalls[3][2];
    u08 numUncheckedBalls = 0;
    BOOL foundBall = FALSE;
    u08 i;

    BOOL stopped = FALSE;
    inSeekPosition = FALSE;

    // Check for balls in two directions (left/right)
    for (i = 0; i < 2; i++)
    {
        ballDist = 0;
        hallHeading = botHeading + lookDir * 64;
        nextNodeNum = botNode;
        numUncheckedBalls = 0;
        // Continue traversing nodes left of right until you hit the end
        while (nextNodeNum > 0)
        {
            /*
             #if DEBUGGING
             lcdWriteStr("N:   H:   ", 0, 0);
             lcdPrintHex(nextNodeNum, 0, 2);
             lcdPrintHex(hallHeading, 0, 7);
             waitFor(RED_BUTTON);
             #endif
             */
            getNode(nextNodeNum, &curNode);
            nextNodeNum = getNodeAtHeading(&curNode, hallHeading);
            if (nextNodeNum > 0)
            {
                getNode(nextNodeNum, &nextNode);
                // Keep track of how far away we are from the bot's current node
                ballDist += getCostToNode(&curNode, nextNodeNum);
                if (isBallNode(nextNodeNum) && !checkedList[nextNodeNum])
                {
                    uncheckedBalls[numUncheckedBalls][BALL_DIST] = ballDist;
                    uncheckedBalls[numUncheckedBalls][BALL_NODE_NUM] =
                                    nextNodeNum;
                    checkedList[nextNodeNum] = TRUE;
                    numUncheckedBalls++;
                }
            }
        }
        // Set pan, tilt, hi-res, etc...

        if (numUncheckedBalls > 0)
        {
            stopped = TRUE;
            trackColorInit(lookDir);

            if (lookDir == -1)
            {
                foundBall |= cameraSeekLeft(uncheckedBalls, numUncheckedBalls);
            } else if (lookDir == 1)
            {
                foundBall |= cameraSeekRight(uncheckedBalls, numUncheckedBalls);
            }
        }

        /*
         #if DEBUGGING
         lcdWriteStr("Seek (  ) for:  ", 0, 0);
         lcdPrintHex(lookDir, 0, 6);
         lcdWriteStr("                ", 1, 0);
         for(j = 0; j < numUncheckedBalls; j++)
         {
         lcdPrintHex(uncheckedBalls[j][BALL_NODE_NUM], 1, 0);
         lcdPrintHex(uncheckedBalls[j][BALL_DIST], 1, 3);
         waitFor(RED_BUTTON);
         }
         waitFor(RED_BUTTON);
         #endif
         */

        lookDir *= -1;  // Look the other way the next time through
    }

    if (stopped)
    {
        moveStraight(0xb, 255);
        setServo(PAN, PAN_CENTER + panOffset);
        setServo(TILT, TILT_FORWARD);
        msDelay(600);
    }

    // Returns true if one or more balls are found
    return foundBall;
}


inline BOOL nodeCode0(void)
{
   BOOL foundBall = FALSE;

   // two virtual windows

   return foundBall;
}


inline BOOL nodeCode22()
{
   BOOL foundBall = FALSE;    // Return value
   u08 scanHeight = 4;
   u08 y = 254;
   u08 scanLimit = 1;
   u08 foundBallNum = 0;

   if (botHeading != 0)
      return FALSE;

   trackColorInit(LOOK_UP);

   // scan from small ground distance to large ground distance
   while ( y - scanHeight > scanLimit )
   {
      y -= scanHeight;
      setVW(1, y-scanHeight, 174, y);
      if ( seeBall() )
      {
         foundBall = TRUE;

         // find ball number of ball at this x
         if( y > 148 )
            foundBallNum = 9;
         else if ( y > 50 )
            foundBallNum = 11;
         else
            foundBallNum = 12;

         addToGoalList( foundBallNum );

#if DEBUGGING
         labelColorStats();
         refreshColorStats();
         //msDelay(1000);
         //clearColorStats();
#endif

/*
#if DEBUGGING
         lcdWriteStr("Added:          ",0,0);
         lcdWriteStr("                ",1,0);
         lcdPrintHex(foundBallNum,1,0);
         waitFor(RED_BUTTON);
#endif
*/
         while ( seeBall() )
         {
            y -= scanHeight;
            setVW(1, y-scanHeight, 174, y);
         }
      }
   }

   setServo(PAN, PAN_CENTER+panOffset);
   setServo(TILT, TILT_FORWARD);
   msDelay(300);

   return foundBall;
}


inline BOOL diagNodeCode(void)
{
   BOOL foundBall = FALSE;

   if( botHeading == N_WEST && (!checkedList[13] || !checkedList[17]) )
   {
      tankTurn(255,tempTweak3);   // tank right
      botHeading += 41;
      foundBall = standardBallSearch();
      botHeading -= 41;
      tankTurn(255, -1*tempTweak3);     // tank left
   }
   else if( botHeading != S_EAST && (!checkedList[14] || !checkedList[15]) )
   {
      tankTurn(255, -1*tempTweak3);     // tank left
      botHeading -= 41;
      foundBall = standardBallSearch();
      botHeading += 41;
      tankTurn(255,tempTweak3);   // tank right
   }

   return foundBall;
}

inline BOOL nodeCode37( void )
{
   BOOL foundBall = FALSE;

   // pass special values into cameraSeekLeft

   return foundBall;
}
