/* testCode.c
 *
 *    Caddy's test code.
 */
#include "testCode.h"

u08 testMode; // = DEFAULT_TEST_MODE;

inline void runTest( void )
{
   switch( testMode )
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
         runBot();
         break;
   }
}

void toggleTestMode( s08 i )
{
   // advance test mode up or down
   testMode += i;
   if( testMode == NUM_TEST_MODES )
      testMode = 0;
   else if( testMode == 255 )
      testMode = NUM_TEST_MODES - 1;

   switch( testMode )
   {
      case SEEK_BALL_TEST_MODE:
#if DEBUGGING
         lcdWriteStr("Seek ball test  ",1,0);
#endif
         break;
      case FIXED_PATH_TEST_MODE:
#if DEBUGGING
         lcdWriteStr("Fixed path test ",1,0);
#endif
         break;
      case UPDATE_PATH_TEST_MODE:
#if DEBUGGING
         lcdWriteStr("Update path test",1,0);
#endif
         break;
      case RUN_BOT_TEST_MODE:
      default:
#if DEBUGGING
         lcdWriteStr("Run bot.        ",1,0);
#endif
         break;
   }
}

void runFixedPath( void )
{
   // From start to zig-zag
   moveToJunction(1, FALSE);
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   moveToJunction(1, TRUE);
   setServo(LIFT, LIFT_OPEN);
   moveToJunction(1, TRUE);
   setServo(LIFT, LIFT_UP);
   
   tractorTurn(255, 64 - turnSubtract);
   
   moveToJunction(1, TRUE);

   setServo(LIFT, LIFT_OPEN);   
   moveToJunction(1, TRUE);
   setServo(LIFT, LIFT_UP);   
   
   // Through zig-zag
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, -64 + turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, -64 + turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, 64 - turnSubtract);
   
   // To bonus ball 1
   moveToJunction(2, TRUE);
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, -64 + turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   
   botHeading = -64;              // Pick up Bonus Ball 1
   bbPositioning(32,0);
   
   // To bonus ball 2
   moveToJunction(1, TRUE);
   tractorTurn(255, -64 + turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   
   botHeading = 64;               // Pick up Bonus Ball 2
   bbPositioning(-96,-128);

   // To nest
   moveToJunction(1, TRUE);
   tractorTurn(255, -64 + turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, -64 + turnSubtract);
   setServo(LIFT, LIFT_OPEN);   
   moveToJunction(1, TRUE);
   setServo(LIFT, LIFT_UP);   
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   tractorTurn(255, 64 - turnSubtract);
   moveToJunction(1, TRUE);
   
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
   
   BOOL justTurned = TRUE;
   NODE node;
   
   
   initGoalList();
   removeFromGoalList(BONUS_BALL_1);
   removeFromGoalList(BONUS_BALL_2);
   removeFromGoalList(SENSOR_NODE);
   
   botNode = tempTweak1;                   // set path to next junction
   botHeading = tempTweak2;                // tempTweak1 must be adjacent to junction at heading in tempTweak2
   
   pathListIndex = 0;
   pathList[0] = botNode;
   getNode( botNode, &node );
   pathList[1] = getNodeAtHeading( &node, botHeading );
   
   
#if DEBUGGING
   lcdWriteStr("Junction Code   ",0,0);
   lcdWriteStr("bn:   bh:       ",1,0);
   lcdPrintDecU08(botNode, 1, 3);
   lcdPrintDecS08(botHeading, 1, 9);
   waitFor(RED_BUTTON);
#endif
   
   moveToJunction(1 , justTurned);
   brake(BOTH);
   msDelay(1000);
   updatePath();                          // sets path to nest, b/c goalList is empty
   junctionCode();                        // updates path to ball, if ball found
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
   
   brake(BOTH);
}

/*
void seekBallTest( void )
{
   u08 goalList[] = {0,0,0,0,0,0,0};
   u08 ndx = 0;
   u08 i = 0;
   
   hiResMode();
   downSample(1, 1);
   
   // Ball 7
#if DEBUGGING
   lcdWriteStr("Ball 7?         ", 0, 0);
   lcdWriteStr("                ", 1, 0);
#endif
   msDelay(1000);
   labelColorStats();
   if ( cameraSeeksBall(69, TILT_VERT+tiltOffset, 90, 128, 174, 254) ) 
   {
      goalList[ndx++] = 7;
      refreshColorStats();
   }
   else
      clearColorStats();
   msDelay(3000);
   
   // Ball 8
#if DEBUGGING
   lcdWriteStr("Ball 8?         ", 0, 0);
   lcdWriteStr("                ", 1, 0);
#endif
   msDelay(1000);
   labelColorStats();
   if ( cameraSeeksBall(70, 113, 90, 1, 174, 128) )
   {
      goalList[ndx++] = 8;
      refreshColorStats();
   }
   else
      clearColorStats();
   msDelay(3000);
   
   // From start to first turn
   moveToJunction(1, FALSE);
   tractorTurn(255, 64 - turnSubtract);
   
   
   // From first turn to node 22
   moveToJunction(1, TRUE);
   moveStraight(-6, 225);

   // Ball 6
#if DEBUGGING
   lcdWriteStr("Ball 6?         ", 0, 0);
   lcdWriteStr("                ", 1, 0);
#endif
   msDelay(1000);
   labelColorStats();
   if ( cameraSeeksBall(71, TILT_VERT+tiltOffset, 131, 1, 174, 254) ) 
   {
      goalList[ndx++] = 6;
      refreshColorStats();
   }
   else
      clearColorStats();
   msDelay(3000);
   
   // Ball 2
#if DEBUGGING
   lcdWriteStr("Ball 2?         ", 0, 0);
   lcdWriteStr("                ", 1, 0);
#endif
   msDelay(1000);
   labelColorStats();
   if ( cameraSeeksBall(0, 0, 1, 1, 130, 254) )
   {
      goalList[ndx++] = 2;
      refreshColorStats();
   }
   else
      clearColorStats();
   msDelay(3000);
   
   // Ball 11 *OR* 12
#if DEBUGGING
   lcdWriteStr("Ball 11 *OR* 12?", 0, 0);
   lcdWriteStr("                ", 1, 0);
#endif
   msDelay(1000);
   labelColorStats();
   if ( cameraSeeksBall(PAN_CENTER+panOffset, 185, 50, 1, 124, 90) )   // << -- SHOULD put in const?
   {
      goalList[ndx++] = 11;
      refreshColorStats();
   }
   else
      clearColorStats();
   msDelay(3000);
   
   // Ball 9
#if DEBUGGING
   lcdWriteStr("Ball 9?         ", 0, 0);
   lcdWriteStr("                ", 1, 0);
#endif
   msDelay(1000);
   labelColorStats();
   if ( cameraSeeksBall(0, 0, 30, 91, 144, 254) )
   {
      goalList[ndx++] = 9;
      refreshColorStats();
   }
   else
      clearColorStats();
   msDelay(3000);
   
   
#if DEBUGGING
   // Print the accumulated goal list
   lcdWriteStr("   balls at:    ", 0, 0);
   lcdWriteStr("                ", 1, 0);
   for (i = 0; i < ndx; i++)
   {
      lcdPrintHex(goalList[i], 1, i*3);
   }
   msDelay(10000);
#endif
   
   // Reset pan/tilt servo positions
   setServo(PAN, PAN_CENTER+panOffset);
   setServo(TILT, TILT_VERT+tiltOffset);
}
*/


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
   runBot();
*/
///*
   // updatePathWithPerms test
   addToGoalList(tempTweak1);
   addToGoalList(tempTweak2);
   addToGoalList(tempTweak3);
   printGoalList();
   waitFor(RED_BUTTON);
   
#if DEBUGGING
   lcdWriteStr("                ",1,0);
   lcdPrintDecU08( updatePath(), 1, 0 );
   printGoalList();
   waitFor(RED_BUTTON);

#endif

   runBot();
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
   lcdWriteStr("Printing...     ",0,0);
   waitFor(RED_BUTTON);
#endif
   u08 i;
   for( i = pathListIndex; i < MAX_PATH_LIST_SIZE; i++)
   {
      if( i % 5 == 0 )
      {
         waitFor(RED_BUTTON);
         lcdWriteStr("                ",0,0);
      }

      lcdPrintDecU08( pathList[i], 0, 3*(i%5) );
   }
   waitFor(RED_BUTTON);
}
