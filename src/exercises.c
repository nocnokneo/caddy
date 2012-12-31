/* exercises.c
 *
 *
 */

#include "exercises.h"

void bbPickupTest(void)
{
    BOOL justTurned = TRUE;
    BOOL firstRun = TRUE;

    while (1)
    {
#if DEBUGGING
        lcdWriteStr("-96 brads, then ", 0, 0);
        lcdWriteStr("-32 brads       ", 1, 0);
#endif
        waitFor(RED_BUTTON);

        //hard left approach
        botNode = 23;
        botHeading = -128;
        pathListIndex = 0;
        pathList[0] = 23;
        pathList[1] = 3;
        pathList[2] = 24;
        pathList[3] = 3;
        pathList[4] = 23;
        justTurned = TRUE;
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        moveToJunction(1, justTurned);
        brake(BOTH);

#if DEBUGGING
        lcdWriteStr("96 brads, then  ", 0, 0);
        lcdWriteStr("32 brads        ", 1, 0);
#endif
        waitFor(RED_BUTTON);

        //Hard right approach
        botNode = 29;
        botHeading = 64;
        pathListIndex = 0;
        pathList[0] = 29;
        pathList[1] = 10;
        pathList[2] = 30;
        pathList[3] = 10;
        pathList[4] = 29;
        justTurned = TRUE;
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        moveToJunction(1, justTurned);
        brake(BOTH);

#if DEBUGGING
        lcdWriteStr("-32 brads, then ", 0, 0);
        lcdWriteStr("-96 brads       ", 1, 0);
#endif
        waitFor(RED_BUTTON);

        if (firstRun)
        {
            addToGoalList(BONUS_BALL_2);
        }

        //Soft Left approach
        botNode = 31;
        botHeading = -64;
        pathListIndex = 0;
        pathList[0] = 31;
        pathList[1] = 30;
        pathList[2] = 31;
        justTurned = TRUE;
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        moveToJunction(1, justTurned);
        brake(BOTH);

        printGoalList();
        waitFor(RED_BUTTON);
    }
}

void zigZagTest(void)
{
    BOOL justTurned = TRUE;

#if DEBUGGING
    lcdWriteStr("botNode = 18    ", 0, 0);
    lcdWriteStr("botHeading = 0  ", 1, 0);
#endif
    waitFor(RED_BUTTON);

    botNode = 40;
    botHeading = 0;
    pathListIndex = 0;
    pathList[0] = 40;
    pathList[1] = 18;
    pathList[2] = 39;
    pathList[3] = 38;
    pathList[4] = 37;
    pathList[5] = 38;
    pathList[6] = 39;
    pathList[7] = 18;
    pathList[8] = 40;

    justTurned = TRUE;
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

#if DEBUGGING
    lcdWriteStr("Assume we do not", 0, 0);
    lcdWriteStr("seek ground ball", 1, 0);
#endif
    msDelay(3000);

    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

#if DEBUGGING
    lcdWriteStr("botNode = 18    ", 0, 0);   //------------------------------
    lcdWriteStr("botHeading = 0  ", 1, 0);
#endif
    waitFor(RED_BUTTON);

    botNode = 40;
    botHeading = 0;
    pathListIndex = 0;
    pathList[0] = 40;
    pathList[1] = 18;
    pathList[2] = 39;
    pathList[3] = 38;
    pathList[4] = 37;
    pathList[5] = 36;
    pathList[6] = 35;
    pathList[7] = 17;
    pathList[8] = 34;

    justTurned = TRUE;
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

#if DEBUGGING
    lcdWriteStr("Assume we seek  ", 0, 0);
    lcdWriteStr("ground ball.    ", 1, 0);
#endif
    msDelay(3000);

    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

#if DEBUGGING
    lcdWriteStr("botNode = 17    ", 0, 0);   //------------------------------
    lcdWriteStr("botHeading = 64 ", 1, 0);
#endif
    waitFor(RED_BUTTON);

    botNode = 34;
    botHeading = 64;
    pathListIndex = 0;
    pathList[0] = 34;
    pathList[1] = 17;
    pathList[2] = 35;
    pathList[3] = 36;
    pathList[4] = 37;
    pathList[5] = 38;
    pathList[6] = 39;
    pathList[7] = 18;
    pathList[8] = 40;

    justTurned = TRUE;
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);
}

void gbPickupTest(void)
{
    BOOL justTurned = TRUE;

    while (1)
    {
#if DEBUGGING
        lcdWriteStr("One ground ball ", 0, 0);  //------------------------------
        lcdWriteStr("(1 junc b4 ball)", 1, 0);
#endif
        waitFor(RED_BUTTON);

        botNode = 22;                     // set path
        botHeading = 0;
        pathListIndex = 0;
        pathList[0] = 22;
        pathList[1] = 9;
        pathList[2] = 29;
        pathList[3] = 11;
        pathList[4] = 12;
        pathList[5] = 33;
        pathList[6] = 13;
        pathList[7] = 34;

        initGoalList();                   // tell bot where balls are
        removeFromGoalList(BONUS_BALL_1);
        removeFromGoalList(BONUS_BALL_2);
        //removeFromGoalList(SENSOR_NODE);
        addToGoalList(11);

        justTurned = TRUE;                // run test
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        moveToJunction(1, FALSE);
        justTurned = positionBot();
        moveToJunction(1, FALSE);
        brake(BOTH);

#if DEBUGGING
        lcdWriteStr("Two ground balls", 0, 0);  //------------------------------
        lcdWriteStr("(1 junc b4 ball)", 1, 0); //  try placing just one ball to test
#endif                                         //  safeguard before turn
        waitFor(RED_BUTTON);
        botNode = 22;                     // set path
        botHeading = 0;
        pathListIndex = 0;
        pathList[0] = 22;
        pathList[1] = 9;
        pathList[2] = 29;
        pathList[3] = 11;
        pathList[4] = 12;
        pathList[5] = 33;
        pathList[6] = 13;
        pathList[7] = 34;

        initGoalList();                   // tell bot where balls are
        removeFromGoalList(BONUS_BALL_1);
        removeFromGoalList(BONUS_BALL_2);
        removeFromGoalList(SENSOR_NODE);
        addToGoalList(11);
        addToGoalList(12);

        justTurned = TRUE;                // run test
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        moveToJunction(1, justTurned);
        brake(BOTH);

#if DEBUGGING
        lcdWriteStr("botNode = 20    ", 0, 0);  //------------------------------
        lcdWriteStr("botHeading =-128", 1, 0); // ( -128 brad turn after pickup )
#endif                                         // make sure nestSequence is called
        waitFor(RED_BUTTON);
        botNode = 20;                     // set path
        botHeading = -128;
        pathListIndex = 0;
        pathList[0] = 20;
        pathList[1] = 41;
        pathList[2] = 5;
        pathList[3] = 41;
        pathList[4] = 42;

        initGoalList();                   // tell bot where balls are
        removeFromGoalList(BONUS_BALL_1);
        removeFromGoalList(BONUS_BALL_2);
        removeFromGoalList(SENSOR_NODE);
        addToGoalList(5);

        justTurned = TRUE;                // run test
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        moveToJunction(1, justTurned);
        justTurned = positionBot();
        nestSequence();
        brake(BOTH);
    }

}

void diagTest(void)
{
    BOOL justTurned = TRUE;

#if DEBUGGING
    lcdWriteStr("botNode = 10    ", 0, 0);
    lcdWriteStr("botHeading = 64 ", 1, 0);
#endif
    waitFor(RED_BUTTON);

    botNode = 10;                     // set path
    botHeading = 64;
    pathListIndex = 0;
    pathList[0] = 10;
    pathList[1] = 30;
    pathList[2] = 31;
    pathList[3] = 15;
    pathList[4] = 14;
    pathList[5] = 34;
    pathList[6] = 13;
    pathList[7] = 33;
    pathList[8] = 13;
    pathList[9] = 34;
    pathList[10] = 14;
    pathList[11] = 15;
    pathList[12] = 31;
    pathList[13] = 30;
    pathList[14] = 10;
    pathList[15] = 29;

    initGoalList();                   // tell bot where balls are
    //addToGoalList(14);
    //addToGoalList(13);

    justTurned = TRUE;                // run test
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();       // Should be -128 brad turn
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

#if DEBUGGING
    lcdWriteStr("botNode = 16    ", 0, 0);   //------------------------------
    lcdWriteStr("botHeading = -64", 1, 0);
#endif
    waitFor(RED_BUTTON);

    botNode = 16;                     // set path
    botHeading = -64;
    pathListIndex = 0;
    pathList[0] = 16;
    pathList[1] = 32;
    pathList[2] = 31;
    pathList[3] = 15;
    pathList[4] = 14;
    pathList[5] = 34;
    pathList[6] = 17;
    pathList[7] = 35;
    pathList[8] = 17;
    pathList[9] = 34;
    pathList[10] = 14;
    pathList[11] = 15;
    pathList[12] = 31;
    pathList[13] = 32;
    pathList[14] = 16;
    pathList[15] = 40;

    initGoalList();                   // tell bot where balls are
    //addToGoalList(15);
    //addToGoalList(17);

    justTurned = TRUE;                // run test
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();       // Should be -128 brad turn
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);
}

void node31Test(void)
{
    BOOL justTurned = TRUE;

#if DEBUGGING
    lcdWriteStr("botNode = 7     ", 0, 0);   //------------------------------
    lcdWriteStr("botHeading = 0  ", 1, 0);
#endif
    waitFor(RED_BUTTON);

    /* initial testing for ball on diagonal
     botNode = 7;                     // set path
     botHeading = 0;
     pathListIndex = 0;
     pathList[0] = 7;
     pathList[1] = 32;
     pathList[2] = 31;
     pathList[3] = 15;
     pathList[4] = 31;
     pathList[5] = 32;
     pathList[6] = 7;
     pathList[7] = 27;
     */
    //testing for diagonal, 2 junctions, and 180 at end of diag
    botNode = 7;                     // set path
    botHeading = 0;
    pathListIndex = 0;
    pathList[0] = 7;
    pathList[1] = 32;
    pathList[2] = 31;
    pathList[3] = 15;
    pathList[4] = 14;
    pathList[5] = 34;
    pathList[6] = 14;
    pathList[7] = 15;
    pathList[8] = 31;
    pathList[9] = 32;
    pathList[10] = 7;
    pathList[11] = 27;

    initGoalList();                   // tell bot where balls are
    //addToGoalList(15);

    /* Initial diag ball test
     justTurned = TRUE;                // run test
     moveToJunction(1, justTurned);
     justTurned = positionBot();
     moveToJunction(1, justTurned);
     justTurned = positionBot();
     moveToJunction(1, justTurned);    // -128 brads, try no ball
     justTurned = positionBot();
     moveToJunction(1, justTurned);
     justTurned = positionBot();
     moveToJunction(1, justTurned);
     brake(BOTH);
     */

    justTurned = TRUE;                // run test
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);    // -128 brads, try no ball
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

#if DEBUGGING
    lcdWriteStr("botNode = 16    ", 0, 0);   //------------------------------
    lcdWriteStr("botHeading = -64", 1, 0);
#endif
    waitFor(RED_BUTTON);

    botNode = 16;                     // set path
    botHeading = -64;
    pathListIndex = 0;
    pathList[0] = 16;
    pathList[1] = 32;
    pathList[2] = 31;
    pathList[3] = 30;
    pathList[4] = 31;
    pathList[5] = 32;
    pathList[6] = 16;
    pathList[7] = 40;

    initGoalList();                   // tell bot where balls are

    justTurned = TRUE;                // run test
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

#if DEBUGGING
    lcdWriteStr("botNode = 16    ", 0, 0);   //------------------------------
    lcdWriteStr("botHeading = -64", 1, 0);
#endif
    waitFor(RED_BUTTON);

    botNode = 16;                     // set path
    botHeading = -64;
    pathListIndex = 0;
    pathList[0] = 16;
    pathList[1] = 32;
    pathList[2] = 7;
    pathList[3] = 27;
    pathList[4] = 7;
    pathList[5] = 32;
    pathList[6] = 31;
    pathList[7] = 30;
    pathList[8] = 31;
    pathList[9] = 32;
    pathList[10] = 7;
    pathList[11] = 27;
    pathList[12] = 7;
    pathList[13] = 32;
    pathList[14] = 16;
    pathList[15] = 40;

    initGoalList();                   // tell bot where balls are

    justTurned = TRUE;                // run test
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    justTurned = positionBot();
    moveToJunction(1, justTurned);
    brake(BOTH);

}
