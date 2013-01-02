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
/**
 * @brief High-level logic controlling Caddy's actions
 */

#include "botCntrl.h"
#include <stdint.h>
#include <stdbool.h>

uint8_t botNode = START_NODE;
int8_t botHeading = START_HEADING;
uint8_t numUnreachedGoals = NUM_GOALS;

static inline int8_t getNextHeading(uint8_t nextBotNode);

inline void runRoborodentiaCourse(void)
{
    bool justTurned = false;
    bool firstRun = true;

    updatePath();

    // run through first leg, skipping positionBot
    junctionCode();
    moveToJunction(1, justTurned);

#if DEBUGGING
    if (lcdMode == NAV_LCD_MODE)
    {
        lcdWriteStr("                ", 0, 0);
        lcdWriteStr("                ", 1, 0);
        lcdPrintDecU08(botNode, 1, 0);
        lcdPrintDecS08(botHeading, 1, 3);
    }
#endif

    // run through arena
    while (pathList[pathListIndex + 1] != STOP_NODE)
    {
        junctionCode();       // ball search, bonous ball pickup, best path code

        justTurned = positionBot();      // turning, preparing for linetracking

        if (firstRun)
        {
            firstRun = false;
            setServo(LIFT, LIFT_OPEN); // Lower lift, on first run, b/c skipping seek at node 21
            msDelay(30);
            upComingBallNum = 1;
            liftDown = true;
        }

#if DEBUGGING
        if (lcdMode == NAV_LCD_MODE)
        {
            lcdPrintDecS08(botHeading, 1, 3);
        }
#endif

        moveToJunction(1, justTurned);   // linetracking, ground ball pickup

#if DEBUGGING
        if (lcdMode == NAV_LCD_MODE)
        {
            lcdPrintDecU08(botNode, 1, 0);
        }
#endif
    }

    if (pathList[pathListIndex + 1] == STOP_NODE)
    {
        positionBot();
        nestSequence();
    }
}

/*
 *  Initializes some of bot's global variables
 */
inline void initBotGlobals(void)
{
    // init bot's path to INITIAL_PATH_LIST
    pathListIndex = 0;
    pathListSize = INITIAL_PATH_LIST_SIZE;
    // (pathList initialized in updatePath.c)

    initGoalList();
    numKnownGoals = NUM_FIXED_GOALS;

    liftDown = false;
    upComingBallNum = 0;
}

/*
 * @brief Turn bot at junctions and, if necessary, ball nodes
 *
 * Maintains botHeading. Performs bonus ball pickup liftDown actions
 *
 * @return True when bot just turned. (Used to tell moveToJunction to
 * begin looking for next junction immediately.)
 *
 * PRE: camera is not streaming
 */
inline bool positionBot(void)
{
    bool justTurned = true;

    int8_t nextHeading = getNextHeading(pathList[pathListIndex + 1]);
    int8_t bradsToTurn = nextHeading - botHeading;

    // BB PICKUP CHECK
    if (botNode == BONUS_BALL_1 && isInGoalList(BONUS_BALL_1))
    {
        bbPositioning(BB1_HEADING, nextHeading);
        removeFromGoalList(BONUS_BALL_1);
    }
    else if (botNode == BONUS_BALL_2 && isInGoalList(BONUS_BALL_2))
    {
        bbPositioning(BB2_HEADING, nextHeading);
        removeFromGoalList(BONUS_BALL_2);
    }

    // TURN/STRAIGHT CHECK
    else if (bradsToTurn != 0)
    {
        int8_t ticksToTurn;
        switch ((int8_t) bradsToTurn)
        {
        case -128: // U-turn
            if (botNode == 37)
            {
                moveToJunction(1, false);
                tickWheels(20, 20, 255);
                msDelay(0x50);
                moveStraight(-20, 255);
            }
            //tankTurn(245, -58);
            tickWheels(-29, 29, 250);
            tankTurn(245, -58);
            break;
        case -105: // Hard Diagonal
            tickWheels(28, 28, 250);     //28
            tractorTurn(255, -tempTweak4);
            tankTurn(250, -70);         //-80
            break;
        case 23: // Soft Diagonal
            tractorTurn(255, 23);       //23
            break;
        case -23:
            tractorTurn(255, -28);
            break;
        case 105:
            tickWheels(17, 17, 250);
            tankTurn(250, 80);          //80
            break;
        default:
            // fixed ticks forward here?

            // convert brads to turn to ticks and turn
            if (bradsToTurn < 0)
            {
                ticksToTurn = bradsToTurn + turnSubtract;
            } else
            {
                ticksToTurn = bradsToTurn - turnSubtract;
            }
            tractorTurn(255, ticksToTurn);
            break;
        }
    }
    else
    {
        justTurned = false;
    }

    if (botNode == SENSOR_NODE)
    {
        removeFromGoalList(SENSOR_NODE);
    }

    // update botHeading
    botHeading = nextHeading;

    // GB PICKUP CHECK: lower lift, if bot knows it will travel over ball
    upComingBallNum = getUpcomingBallNum();
    if (upComingBallNum != 0)
    {
        setServo(LIFT, LIFT_OPEN);
        msDelay(30);
        liftDown = true;
    }

    return justTurned;
}

/*
 * Returns absolute heading of next node given botNode and the next botNode.
 */
static inline int8_t getNextHeading(uint8_t nextBotNode)
{
    NODE nextNode;            // info about nodes adjacent to botNode
    int8_t nextNodeIndex;        // nextNode offset to nextBotNode
    int8_t nextHeading;          // absolute direction to nextBotNode

    // get absolute direction of nextBotNode from node list
    getNode(botNode, &nextNode);
    if (&nextNode == NULL )
    {
#if DEBUGGING
        lcdWriteStr("nodeList error  ", 0, 0);
#endif
        while (1) ;
    }
    nextNodeIndex = findValue(nextNode.adjNodes,
                              nextNode.numAdjNodes,
                              nextBotNode);

    // get next heading or report error
    if (nextNodeIndex == -1)
    {
#if DEBUGGING
        lcdWriteStr("pathList error  ", 0, 0);
#endif
        brake(BOTH);
        while (1) ;
    }
    nextHeading = nextNode.adjHeadings[nextNodeIndex];

    return nextHeading;
}

/* Rotates bot before and after Bonus Ball grab
 *    bbHeading   - heading bot must have for bb pickup.
 *    nextHeading - heading bot must have after bb pickup
 */
inline void bbPositioning(int8_t bbHeading, int8_t nextHeading)
{
    // move forward (camera will be over junction at this point)
    // May or may not need to move foward (requires testing)
    //    Some are fine without foward, some seem to need it
    //    Right now, only -32 case moves forward

    // rotate by (bbHeading - botHeading)
    switch ((int8_t) (bbHeading - botHeading))
    {
    case 96:
        // example of 96 brad rotation
        tickWheels(28, 0, 255); // allows fluid motion (no overshoot correction)
        tankTurn(255, 58);      //58
        break;
    case -96:
        tickWheels(0, 28, 255); // allows fluid motion (no overshoot correction)
        tankTurn(255, -64);     //-64
        break;
    case -32:
        tickWheels(10, 10, 255); //10 Move bot forward a few ticks to make it correctly aligned
        tickWheels(0, 32, 255);                   //28
        break;
    default:
#if DEBUGGING
        lcdWriteStr("ERROR:          ", 0, 0);
        lcdWriteStr("Turn Amt =      ", 1, 0);
        lcdPrintDecS08(bbHeading - botHeading, 1, 11);
        brake(BOTH);
        while (1) ;
#endif
        break;
    }

    grabBonusBall(); // Grab the BB

    // Rotate by (nextHeading - bbHeading)
    // (This should only be 32, -32, or -96)
    switch ((int8_t) (nextHeading - bbHeading))
    {
    case 32:
        tankTurn(250, 32);
        break;
    case -32:
        tankTurn(250, -32);
        break;
    case -96:
        tankTurn(250, -90);
        break;
    default:         // Error, this should only be 32, -32, or -96
#if DEBUGGING
        lcdWriteStr("ERROR:          ", 0, 0);
        lcdWriteStr("nH - bbH =      ", 1, 0);
        lcdPrintDecS08(bbHeading - botHeading, 1, 11);
        brake(BOTH);
        while (1) ;
#endif
        break;
    }
}

/*
 * Moves to next junction in pathList.
 */
inline void moveToJunction(uint8_t numJunctions, bool justTurned)
{
    bool onLine = true;
    bool juncApproaching = false;
    uint8_t juncCount = 0;

    uint8_t ignoreJuncCount;
    if (!justTurned)
    {
        ignoreJuncCount = 3;
    } else
    {
        ignoreJuncCount = 0;
    }

    uint8_t pickingUp = false;
    uint8_t pickingUpCount = 0;

    uint8_t ignoreBreakBeamCount = BEAM_IGNORE_COUNT;

    trackLineInit();

    // Linetrack, until bot is at junction or nest.
    // If see ground ball, pickup it up and continue linetracking.
    while (onLine)
    {
        while (lineStatsProcessed) ;

        analyzeLineStats();
        adjustPWM();

        // CURRENT JUNCTION IGNORE
        if (ignoreJuncCount > 0 && junctionY == 0)
        {
            ignoreJuncCount--;
        }

        // JUNCTION CHECK
        if (ignoreJuncCount == 0 && junctionY != 0)
        {
            if (junctionY < turnPoint)
            {
                juncApproaching = true;
            } else if (juncApproaching)
            {
                juncApproaching = false;
                juncCount++;

                // set botNode to next junction in pathList
                do
                {
                    pathListIndex++;
                    botNode = pathList[pathListIndex];
                } while (!isJunction(botNode));

                // Break out of line tracking
                if (juncCount >= numJunctions)
                {
                    onLine = false;
                }
            }
        }

        // STOP IGNORING BEAM CHECK
        if (liftDown && ignoreBreakBeamCount != 0)
        {
            ignoreBreakBeamCount--;
        }

        // BEGIN PICKUP CHECK
        if (liftDown && ignoreBreakBeamCount == 0 && BREAK_BEAM_TRIGGERED)
        {
            streamModeOff();
            setServo(LIFT, LIFT_CORRAL); // Perhaps raise it slowly if there are pick-up problems
            msDelay(30);
            trackLineInit();

            liftDown = false;
            pickingUp = true;
            pickingUpCount = 0;
        }

        // COMPLETE/STOP LIFTING CHECK
        if (pickingUp)
        {
            pickingUpCount++;

            if (pickingUpCount == CORRAL_COUNT)
            {
                streamModeOff();
                setServo(LIFT, LIFT_UP);
                trackLineInit();
            }

            if (pickingUpCount == LIFT_DONE_COUNT)
            {
                pickingUp = false;

                // Set current botNode to node where this ball is
                botNode = upComingBallNum;
                removeFromGoalList(upComingBallNum);

                if (upComingBallNum == 1) // account for ball not found by camera prior to pickup
                {
                    numKnownGoals++;
                }

                // Find correct pathListIndex
                while (botNode != pathList[pathListIndex])
                {
                    pathListIndex++;
                }

                streamModeOff();      // Turn off line tracking
                disableServo(LIFT);
                positionBot(); // In case we want to make a -128 brad turn after picking up ball
                ignoreBreakBeamCount = BEAM_IGNORE_COUNT;
                trackLineInit();      // Turn line tracking back on
            }

        }
    }

    streamModeOff();

    // Make sure lift is up (in case we missed a ball or incorrectly thought one was there)
    if (liftDown)
    {
        brake(BOTH);
#if DEBUGGING
        lcdWriteStr("No ball         ", 0, 0);
#endif
        setServo(LIFT, LIFT_UP);    // Raise the lift
        msDelay(700);
        disableServo(LIFT);
        liftDown = false;

        // correct goal state
        removeFromGoalList(upComingBallNum);
        numUnreachedGoals--;
        numKnownGoals--;
    }
}

void nestSequence(void)
{
    // line track, until NEST_BUTTON is pressed
    trackLineInit();

    while (!justPressed(NEST_BUTTON))
    {
        if (!lineStatsProcessed)
        {
            analyzeLineStats();
            adjustPWM();
        }

        debounceButtons();
    }

    brake(BOTH);
    streamModeOff();
    setServo(LIFT, LIFT_UP);       // Turn lift on
    msDelay(300);

    // Open door, back up, close door
    setServo(DOOR, DOOR_OPEN);
    moveStraight(-1, 255);              // Back up to take pressure off button
    brake(BOTH);
    //myDelay(25);                     // Let balls roll out
    msDelay(3000);
    setServo(DOOR, DOOR_CLOSED); // Leaves door closed, so lift and door don't colide on power up.
    //myDelay(10);                     // Wait for door to close
    msDelay(1000);

    // Disable all servos
    disableServo(PAN);
    disableServo(TILT);
    disableServo(BOOM);
    disableServo(LIFT);
    disableServo(DOOR);
}
