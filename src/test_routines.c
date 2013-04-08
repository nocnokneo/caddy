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
#include "test_routines.h"
#include "robot_control.h"
#include "motor_control.h"
#include "ball_tracking.h"
#include "line_tracking.h"
#include "path_planning.h"
#include "node_list.h"
#include "servos.h"
#include "buttons.h"
#include "tweak_data.h"
#include "lcd_16x2.h"
#include "utility.h"

// avr-libc
#include <stdbool.h>

inline void runTest(void)
{
    switch (testMode)
    {
    case SEEK_BALL_TEST_MODE:
        seekBallTest();
        break;
    case FIXED_PATH_TEST_MODE:
        runFixedPath();
        break;
    case UPDATE_PATH_TEST_MODE:
        updatePathTest();
        break;
    case RUN_BOT_TEST_MODE:
    default:
        runRoborodentiaCourse();
        break;
    }
}

void toggleTestMode(int8_t i)
{
    // advance test mode up or down
    testMode += i;
    if (testMode == NUM_TEST_MODES)
        testMode = 0;
    else if (testMode == 255)
        testMode = NUM_TEST_MODES - 1;

    switch (testMode)
    {
    case SEEK_BALL_TEST_MODE:
#if DEBUGGING
        lcdWriteStr("Seek ball test  ", 1, 0);
#endif
        break;
    case FIXED_PATH_TEST_MODE:
#if DEBUGGING
        lcdWriteStr("Fixed path test ", 1, 0);
#endif
        break;
    case UPDATE_PATH_TEST_MODE:
#if DEBUGGING
        lcdWriteStr("Update path test", 1, 0);
#endif
        break;
    case RUN_BOT_TEST_MODE:
    default:
#if DEBUGGING
        lcdWriteStr("Run bot.        ", 1, 0);
#endif
        break;
    }
}

void runFixedPath( void )
{
    // From start to zig-zag
    moveToJunction(1, false);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);
    moveToJunction(1, true);
    setServo(LIFT, LIFT_OPEN);
    moveToJunction(1, true);
    setServo(LIFT, LIFT_UP);

    tractorTurn(255, 64 - turnSubtract);

    moveToJunction(1, true);

    setServo(LIFT, LIFT_OPEN);
    moveToJunction(1, true);
    setServo(LIFT, LIFT_UP);

    // Through zig-zag
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, -64 + turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, -64 + turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, 64 - turnSubtract);

    // To bonus ball 1
    moveToJunction(2, true);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, -64 + turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);

    botHeading = -64;              // Pick up Bonus Ball 1
    bonusBallPickUpManeuver(32, 0);

    // To bonus ball 2
    moveToJunction(1, true);
    tractorTurn(255, -64 + turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);

    botHeading = 64;               // Pick up Bonus Ball 2
    bonusBallPickUpManeuver(-96, -128);

    // To nest
    moveToJunction(1, true);
    tractorTurn(255, -64 + turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, -64 + turnSubtract);
    setServo(LIFT, LIFT_OPEN);
    moveToJunction(1, true);
    setServo(LIFT, LIFT_UP);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);
    tractorTurn(255, 64 - turnSubtract);
    moveToJunction(1, true);

    nestSequence();
}


void seekBallTest( void )
{
    /*
     trackColorInit(LOOK_LEFT);

     while( 1 )
     {
     labelColorStats();
     if (cameraSeekLeft() )
     {
     //msDelay(1000);
     //lcdWriteStr("BALL            ", 0, 0);
     }
     else
     {
     //msDelay(1000);
     //lcdWriteStr("NO BALL         ", 0, 0);
     }
     msDelay(1000);
     }
     */

    bool justTurned = true;
    NODE node;

    botNode = tempTweak1;                   // set path to next junction
    botHeading = tempTweak2; // tempTweak1 must be adjacent to junction at heading in tempTweak2

    pathListIndex = 0;
    pathList[0] = botNode;
    getNode(botNode, &node);
    pathList[1] = getNodeAtHeading(&node, botHeading);

#if DEBUGGING
    lcdWriteStr("Junction Code   ", 0, 0);
    lcdWriteStr("bn:   bh:       ", 1, 0);
    lcdPrintDecU08(botNode, 1, 3);
    lcdPrintDecS08(botHeading, 1, 9);
    waitFor(RED_BUTTON);
#endif

    moveToJunction(1, justTurned);
    brake(BOTH_MOTORS);
    msDelay(1000);
    updatePath();                    // sets path to nest, b/c goalList is empty
    junctionCode();                       // updates path to ball, if ball found
    /*
     #if DEBUGGING
     lcdWriteStr("Junction Code   ",0,0);
     printGoalList();
     #endif

     justTurned = positionBot();           // continues to nest or picks up ball
     moveToJunction(1 , justTurned);

     //junctionCode();
     //justTurned = positionBot();
     //moveToJunction(1 , justTurned);
     */

    printGoalList();

    brake(BOTH_MOTORS);
}


inline void refreshColorStats( void )
{
#if DEBUGGING
    lcdPrintHex(lineStats[0][MX_NDX], 0, 1);
    lcdPrintHex(lineStats[0][MY_NDX], 0, 4);
    lcdPrintHex(lineStats[0][X1_NDX], 0, 9);
    lcdPrintHex(lineStats[0][Y1_NDX], 0, 12);
    lcdPrintHex(lineStats[0][PIXEL_CNT_NDX], 1, 1);
    lcdPrintHex(lineStats[0][CONFIDENCE_NDX], 1, 5);
    lcdPrintHex(lineStats[0][X2_NDX], 1, 10);
    lcdPrintHex(lineStats[0][Y2_NDX], 1, 13);
#endif
}


inline void clearColorStats( void )
{
#if DEBUGGING
    lcdWriteStr("  ", 0, 1);
    lcdWriteStr("  ", 0, 4);
    lcdWriteStr("  ", 0, 9);
    lcdWriteStr("  ", 0, 12);
    lcdWriteStr("  ", 1, 1);
    lcdWriteStr("  ", 1, 5);
    lcdWriteStr("  ", 1, 10);
    lcdWriteStr("  ", 1, 13);
#endif
}


inline void labelColorStats( void )
{
#if DEBUGGING
    lcdWriteStr("(  ,  ) (  ,  ) ", 0, 0);
    lcdWriteStr("p   c    (  ,  )", 1, 0);
#endif
}


void updatePathTest( void )
{
    /*
     //Break beam test
     while(1)
     {
     #if DEBUGGING
     if( BREAK_BEAM_TRIGGERED )
     {
     lcdWriteStr("Triggered       ", 0, 0);
     }
     else
     {
     lcdWriteStr("Not triggered   ", 0, 0);
     }
     #endif
     }
     */

    /*
     #if DEBUGGING
     // Uniform Cost Search Test
     lcdPrintDecU08( uniformCostSearch(tempTweak1,tempTweak2), 1, 0 );
     while(1) ;
     #endif
     */

    /*
     // reconstruct path test
     updatePathTo(tempTweak1);
     runRoborodentiaCourse();
     */
///*
    // updatePathWithPerms test
    addToGoalList(tempTweak1);
    addToGoalList(tempTweak2);
    addToGoalList(tempTweak3);
    printGoalList();
    waitFor(RED_BUTTON);

#if DEBUGGING
    lcdWriteStr("                ", 1, 0);
    lcdPrintDecU08(updatePath(), 1, 0);
    printGoalList();
    waitFor(RED_BUTTON);
#endif

    runRoborodentiaCourse();
//*/

}

void printPathList( void )
{
#if DEBUGGING
    lcdPrintDecU08(botNode, 1, 0);
    lcdPrintDecS08(botHeading, 1, 3);
    lcdPrintDecU08(pathListIndex, 1, 6);
#endif

    // print pathList
#if DEBUGGING
    lcdWriteStr("Printing...     ", 0, 0);
    waitFor(RED_BUTTON);
#endif
    uint8_t i;
    for (i = pathListIndex; i < MAX_PATH_LIST_SIZE; i++)
    {
        if (i % 5 == 0)
        {
            waitFor(RED_BUTTON);
            lcdWriteStr("                ", 0, 0);
        }

        lcdPrintDecU08(pathList[i], 0, 3 * (i % 5));
    }
    waitFor(RED_BUTTON);
}
