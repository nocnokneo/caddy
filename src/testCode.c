/* testCode.c
 *
 *    Caddy's test code.
 */
#include "testCode.h"

u08 testMode = DEFAULT_TEST_MODE;

inline void runTest( void )
{
   switch( testMode )
   {
      case BB_TEST_MODE:
         bbPickupTest();
         break;
      case GB_TEST_MODE:
         gbPickupTest();
         break;
      case LINE_STATS_TEST_MODE:
         lineStatsTest();
         break;
      case SEE_BALL_TEST_MODE:
         seeBallTest();
         break;
      case SEEK_BALL_TEST_MODE:
//         seekBallTest();
         break;
      case NEST_TEST_MODE:
         nestSequence();
         break;
      case FIXED_PATH_TEST_MODE:
         runFixedPath();
         break;
      case ZIG_ZAG_TEST_MODE:
         zigZagTest();
         break;
      case UPDATE_PATH_TEST_MODE:
         updatePathTest();
         break;
      case DIAG_TEST_MODE:
         diagTest();
         break;
      case NODE_31_TEST_MODE:
         node31Test();
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
      case BB_TEST_MODE:
         lcdWriteStr("Bonus ball test ",1,0);
         break;
      case GB_TEST_MODE:
         lcdWriteStr("Ground ball test",1,0);
         break;
      case LINE_STATS_TEST_MODE:
         lcdWriteStr("Line stats test ",1,0);
         break;
      case SEE_BALL_TEST_MODE:
         lcdWriteStr("See ball test   ",1,0);
         break;
      case SEEK_BALL_TEST_MODE:
         lcdWriteStr("Seek ball test  ",1,0);
         break;
      case NEST_TEST_MODE:
         lcdWriteStr("Nest test       ",1,0);
         break;
      case FIXED_PATH_TEST_MODE:
         lcdWriteStr("Fixed path test ",1,0);
         break;
      case ZIG_ZAG_TEST_MODE:
         lcdWriteStr("Zig zag test    ",1,0);
         break;
      case UPDATE_PATH_TEST_MODE:
         lcdWriteStr("Update path test",1,0);
         break;
      case DIAG_TEST_MODE:
         lcdWriteStr("Diagonal test   ",1,0);
         break;
      case NODE_31_TEST_MODE:
         lcdWriteStr("Node 31 test    ",1,0);
         break;
      case RUN_BOT_TEST_MODE:
      default:
         lcdWriteStr("Run bot.        ",1,0);
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


void baseSpeedTest( void )
{     
   myDelay(70);
   forward(LEFT_MOTOR, l_base);
   forward(RIGHT_MOTOR, r_base);
   myDelay(200);
   brake(BOTH);
}

void lineStatsTest( void )
{
   disableMotors();
   trackLineInit();
   while ( 1 ) 
   {
      // line track
      while(lineStatsProcessed);
      analyzeLineStats();
   }
}


void seeBallTest( void )
{
   //u08 i = 0;
   
   labelColorStats();
   
   // change pixel res/range to line mode's settings
   lowResMode();
   rprintf("DS %d %d\r", DS_X_LINE, DS_Y_LINE);
   rprintf("vw %d %d %d %d\r", VW_X1_LINE, VW_Y1_LINE, VW_X2_LINE, VW_Y2_LINE);
   
   while (1)
   {
      //lcdPrintHex(i++, 0, 14);
      if ( getBallY() != 0 ) 
      {
         refreshColorStats();
      }
      else
      {
         clearColorStats();
      }
      
   }
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
   lcdWriteStr("(  ,  ) (  ,  ) ", 0, 0);
   lcdWriteStr("p   c    (  ,  )", 1, 0);
}

void encoderTest( void )
{
   encoderSetPosition(LEFT_ENC, 0);
   encoderSetPosition(RIGHT_ENC, 0);

   moveToJunction(2, TRUE);
   
   brake(BOTH);
}



void updatePathTest( void )
{
/*
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

#if DEBUGGING
   //lcdPrintDecU08( uniformCostSearch(tempTweak1,tempTweak2 /*,searchSpace*/ ), 1, 0 );
#endif
 
   
   updatePathTo(tempTweak1);
   runBot();
   

}
