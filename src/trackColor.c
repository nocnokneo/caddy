/* trackColor.c
 *
 *    Identifies and ranges orange ground balls.
 *    Identifies nest.
 *
 */

#include "trackColor.h"

void trackColorInit(s08 dir)
{
   if (!inSeekPosition)
   {
      brake(BOTH);
      msDelay(200);
      moveStraight(-1*0xb, 255);
      inSeekPosition = TRUE;
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
   
   // Track red
   //rprintf("ST %d %d %d %d %d %d\r", BALL_RMIN, BALL_RMAX, BALL_GMIN, BALL_GMAX, BALL_BMIN, BALL_BMAX);
}


/*
 * Returns Y1 (top of ball) if camera sees a ball, zero otherwise
 */
u08 getBallY( void ) 
{
   rprintf("lm 0 0\r");

   // Mask everything but the 'My' value
   //rprintf("OM 0 2\r");                             //<- NO MASKING?
   
   // Change to poll mode so only one packet is sent
   rprintf("PM 1\r");
   
   // Track red
   rprintf("TC %d %d %d %d %d %d\r", BALL_RMIN, BALL_RMAX, BALL_GMIN, BALL_GMAX, BALL_BMIN, BALL_BMAX);
    
   colorStatsProcessed = TRUE;
   while (colorStatsProcessed) ;
      
   return (lineStats[0][Y1_NDX]);
}


BOOL seeBall( void ) 
{
   // Track red
   rprintf("TC %d %d %d %d %d %d\r", BALL_RMIN, BALL_RMAX, BALL_GMIN, BALL_GMAX, BALL_BMIN, BALL_BMAX);
   colorStatsProcessed = TRUE;
   while (colorStatsProcessed) ;
      
   return lineStats[0][Y1_NDX] > 0;
}


/* 
 * Just does left seeks
 *    PRE - the longest check is the last element of the uncheckedBalls array
 * 
 *    uncheckedBalls - ball node numbers and ground distances away from bot
 */
BOOL cameraSeekLeft( u08 uncheckedBalls[][2], u08 numUncheckedBalls )
{
   BOOL foundBall = FALSE;    // Return value
   u08 scanHeight = 4;
   u08 x = 174;
   //u08 ballDist[3];
   //u08 ballCount = 0;
   u08 scanLimit = distToPix( uncheckedBalls[numUncheckedBalls-1][BALL_DIST] + 1 );
   
   // get pixel ranges for unchecked balls passed in
   u08 i = 0;
   u08 maxBallX[3];
   while( i+1 < numUncheckedBalls )
   {
      maxBallX[i] = ( distToPix( uncheckedBalls[i][BALL_DIST] ) +
                       distToPix( uncheckedBalls[i+1][BALL_DIST] ) ) / 2;
      i++;
   }
   maxBallX[i] = scanLimit;

/*
#if DEBUGGING   
   lcdWriteStr("maxBallX =      ",0,0);
   lcdWriteStr("                ",1,0);
   for( i = 0; i < numUncheckedBalls; i++ )
   {
      lcdPrintHex(maxBallX[i],1,3*i);
   }
   waitFor(RED_BUTTON);
#endif
*/
   
   // scan from small ground distance to large ground distance
   while ( x - scanHeight > scanLimit )
   {
      x -= scanHeight;
      setVW(x-scanHeight, 1, x, 254);
      if ( seeBall() )
      {
         foundBall = TRUE;
         //ballDist[ballCount++] = xToDist(x);
         
         // find ball number of ball at this x
         i = 0;
         while( maxBallX[i] > x )
         {
            i++;
         }
         addToGoalList( uncheckedBalls[i][BALL_NODE_NUM] );
         
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
         lcdPrintHex(uncheckedBalls[i][BALL_NODE_NUM],1,0);
         waitFor(RED_BUTTON);
#endif
*/
         
         while ( seeBall() )
         {
            x -= scanHeight;
            setVW(x-scanHeight, 1, x, 254);
         }
      }
   }
   
   return foundBall;
}

// returns pixel equivalant of 'distance'
u08 distToPix( u08 distance )
{
   switch( distance )
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
BOOL cameraSeekRight( u08 uncheckedBalls[][2], u08 numUncheckedBalls )
{
   BOOL foundBall = FALSE;    // Return value
   u08 scanHeight = 4;
   u08 x = 0;
   //u08 ballDist[3];
   //u08 ballCount = 0;
   u08 scanLimit = 174 - distToPix( uncheckedBalls[numUncheckedBalls-1][BALL_DIST] + 1 );
   
   // get pixel ranges for unchecked balls passed in
   u08 i = 0;
   u08 maxBallX[3];
   while( i+1 < numUncheckedBalls )
   {
      maxBallX[i] = ( (174 - distToPix( uncheckedBalls[i][BALL_DIST] )) +
                       (174 - distToPix( uncheckedBalls[i+1][BALL_DIST] )) ) / 2;
      i++;
   }
   maxBallX[i] = scanLimit;

/*
#if DEBUGGING   
   lcdWriteStr("maxBallX =      ",0,0);
   lcdWriteStr("                ",1,0);
   for( i = 0; i < numUncheckedBalls; i++ )
   {
      lcdPrintHex(maxBallX[i],1,3*i);
   }
   waitFor(RED_BUTTON);
#endif
*/
   
   // scan from small ground distance to large ground distance
   while ( x + scanHeight < scanLimit )
   {
      x += scanHeight;
      setVW(x, 1, x+scanHeight, 254);
      if ( seeBall() )
      {
         foundBall = TRUE;
         //ballDist[ballCount++] = xToDist(x);
         
         // find ball number of ball at this x
         i = 0;
         while( maxBallX[i] < x )
         {
            i++;
         }
         addToGoalList( uncheckedBalls[i][BALL_NODE_NUM] );
         
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
         lcdPrintHex(uncheckedBalls[i][BALL_NODE_NUM],1,0);
         waitFor(RED_BUTTON);
#endif
*/
         
         while ( seeBall() )
         {
            x += scanHeight;
            setVW(x, 1, x+scanHeight, 254);
         }
      }
   }
   
   return foundBall;
}

