/* trackColor.c
 *
 *    Identifies and ranges orange ground balls.
 *    Identifies nest.
 *
 */

#include "trackColor.h"

void trackColorInit(void)
{

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
   hiResMode();
   rprintf("LM 0 0\r");

   // Change to poll mode so only one packet is sent
   rprintf("PM 1\r");
   
   // Track red
   rprintf("TC %d %d %d %d %d %d\r", BALL_RMIN, BALL_RMAX, BALL_GMIN, BALL_GMAX, BALL_BMIN, BALL_BMAX);
    
   colorStatsProcessed = TRUE;
   while (colorStatsProcessed) ;
      
   return lineStats[0][Y1_NDX] > 0;
}


/* 
 * Returns true if the camera locates a ball at the specified distance 
 * from the bot. Units are in inches. Direction is 1 for right, -1 for left.
 */ 
/*
BOOL cameraSeeksBall( u08 ballDist, s08 dir ) 
{
   u16 a_squared, b_squared;
   u08 panPosition = 0;
   u08 vwSize = 0;
   
   // Set camera so right/left edge of image just passes ball
   panPosition = PAN_CENTER+panOffset + (atan((ballDist + dir*(GROUND_FOV/2)) / CAM_HEIGHT) * PAN_TICKS_PER_DEG);
   setServo(PAN, panPosition);
   
   // Set virtual window so left/right edge falls just short of ball
   a_squared = CAM_HEIGHT^2 + (ballDist + dir*GROUND_FOV/2)^2;
   b_squared = CAM_HEIGHT^2 + (ballDist - dir*GROUND_FOV/2)^2;
   vwSize = acos((groundFOV^2 - a_sqared - b_squared) / (-2 * sqrt(a_squared) * sqrt(b_squared))) 
            * X_PIXELS_PER_DEG;
            
   // No downsampling - must set this before VW command
   rprintf("DS 1 1\r");
   if ( dir == LOOK_RIGHT ) 
      rprintf("VW %d %d %d %d\r", VW_X1_SEEK-vwSize, VW_Y1_SEEK, VW_X2_SEEK, VW_Y2_LINE);
   else 
      rprintf("VW %d %d %d %d\r", VW_X1_SEEK, VW_Y1_SEEK, VW_X2_SEEK+vwSize, VW_Y2_LINE);

   rprintf("st %d %d %d %d %d %d\r", BALL_RMIN, BALL_RMAX, BALL_GMIN, 
           BALL_GMAX, BALL_BMIN, BALL_GMAX);
}
*/

/*
BOOL cameraSeeksBall(u08 pan, u08 tilt, u08 x1, u08 y1, u08 x2, u08 y2)
{
   // Set pan and tilt to look at ball
   if (pan > 0)
      setServo(PAN, pan);
   if (tilt > 0)
      setServo(TILT, tilt);
   // Crop out extra crap with virtual window command
   setVW(x1, y1, x2, y2);
   // Wait for servos to get into position (if they had to move)
   if (pan > 0 || tilt > 0)
      msDelay(700);
   
   if (getBallY() > 0)
      return TRUE;
   return FALSE;
}
*/


/* 
 * Just does left seeks
 *    PRE - the longest check is the last element of the uncheckedBalls array
 * 
 *    uncheckedBalls - ball node numbers and ground distances away from bot
 */
BOOL cameraSeekLeft( u08 uncheckedBalls[][2], u08 numUncheckedBalls )
{
   BOOL foundBall = FALSE;    // Return value
   u08 scanHeight = 0;
   u08 x = 174;
   u08 ballDist[3];
   u08 ballCount = 0;
   u08 scanLimit = 174 - distToX(uncheckedBalls[numUncheckedBalls-1][BALL_DIST]);
   
   // Set pan (center) and tilt
   setServo(PAN, PAN_CENTER + panOffset - PAN_SEEK_OFFSET);
   msDelay(500);
   while ( x - scanHeight > scanLimit )
   {
      x -= scanHeight;
      scanHeight = 4;   // may need to use an equation to get a scan line
                        // of diminishing size
      setVW(x-scanHeight, 1, x, 254);
      if ( seeBall() )
      {
         foundBall = TRUE;
         ballDist[ballCount++] = xToDist(x-scanHeight);
         while ( seeBall() )
         {
            x -= scanHeight;
            scanHeight = 4;
            setVW(x-scanHeight, 1, x, 254);
         }
      }
   }
   
   // Need to update goal list with node numbers that correspond to ballDist
   
   return foundBall;
}


BOOL cameraSeekRight( u08 uncheckedBalls[][2], u08 numUncheckedBalls )
{
   // TODO
   return FALSE;
}


// TODO...
BOOL specialSeek22( void )
{
   checkedList[9] =  TRUE;
   checkedList[11] = TRUE;
   checkedList[12] = TRUE;
   return FALSE;
   /*
   u08 ballDist[3] = {0,0,0};
   u08 ballCount = 0;
   u08 scanHeight = 0;
   u08 y = 254;
   maxScan = correlateYtoDist(maxScan);
   
   // Set pan (center) and tilt
   while ( y > (maxScan + scanHeight))
   {
      y -= scanHeight;
      scanHeight = y/10 + 5.4;
      setVW(1, y-scanHeight, 174, y);
      if ( seeBall() )
      {
         ballBottom = y;
         while ( seeBall() )
         {
            y -= scanHeight;
            scanHeight = y/10 + 5.4;
            setVW(1, y-scanHeight, 174, y);
         }
         ballDist[ballCount++] = correlateYtoDist(avg(ballBottom, y));
      }
   }
   */
}

u08 xToDist(u08 y)
{
   return 1;
}


u08 distToX(u08 dist)
{
   return 1;
}
